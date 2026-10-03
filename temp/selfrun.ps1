$ErrorActionPreference = 'Stop'
Add-Type -Namespace W -Name U -MemberDefinition @'
[DllImport("user32.dll", SetLastError=true)]
public static extern bool EnumWindows(EnumProc cb, IntPtr lp);
public delegate bool EnumProc(IntPtr h, IntPtr lp);
[DllImport("user32.dll")]
public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
[DllImport("user32.dll", CharSet=CharSet.Unicode)]
public static extern bool PostMessageW(IntPtr h, uint msg, IntPtr wp, IntPtr lp);
'@

function Get-WindowForPid([int]$want) {
    $found = [IntPtr]::Zero
    $cb = [W.U+EnumProc]{
        param($h, $lp)
        $pid2 = 0
        [void][W.U]::GetWindowThreadProcessId($h, [ref]$pid2)
        if ($pid2 -eq $want) { $script:found = $h; return $false }
        return $true
    }
    [void][W.U]::EnumWindows($cb, [IntPtr]::Zero)
    return $script:found
}

$outDir = Join-Path $PWD 'x64\Debug'
Get-Process -Name MapGenerator -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Seconds 1

$before = @(Get-ChildItem -Path $outDir -Filter 'rmg_*.map' | ForEach-Object { $_.Name })
$p = Start-Process -FilePath (Join-Path $outDir 'MapGenerator.exe') -WorkingDirectory $outDir -PassThru
$h = [IntPtr]::Zero
for ($i = 0; $i -lt 20; $i++) {
    Start-Sleep -Milliseconds 500
    $h = Get-WindowForPid $p.Id
    if ($h -ne [IntPtr]::Zero) { break }
}
Write-Output ('pid=' + $p.Id + ' hwnd=' + $h)
if ($h -eq [IntPtr]::Zero) { Write-Output 'window not found'; exit 1 }

[void][W.U]::PostMessageW($h, 0x0111, [IntPtr]101, [IntPtr]::Zero)
$new = $null
for ($i = 0; $i -lt 200; $i++) {
    Start-Sleep -Seconds 2
    $cur = @(Get-ChildItem -Path $outDir -Filter 'rmg_*.map' | ForEach-Object { $_.Name })
    $diff = @($cur | Where-Object { $before -notcontains $_ })
    if ($diff.Count -gt 0) { $new = $diff; break }
}
if ($new) { Write-Output ('new map: ' + ($new -join ',')) } else { Write-Output 'no new map' }
Start-Sleep -Seconds 3
[void][W.U]::PostMessageW($h, 0x0010, [IntPtr]::Zero, [IntPtr]::Zero)
Start-Sleep -Seconds 3
if (-not $p.HasExited) { $p.Kill() }
Write-Output 'done'

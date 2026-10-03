param([int]$EnvIdx = 4)
$ErrorActionPreference = 'Stop'
Add-Type -Namespace W -Name U2 -MemberDefinition @'
[DllImport("user32.dll", SetLastError=true)]
public static extern bool EnumWindows(EnumProc cb, IntPtr lp);
public delegate bool EnumProc(IntPtr h, IntPtr lp);
[DllImport("user32.dll")]
public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
[DllImport("user32.dll", CharSet=CharSet.Unicode)]
public static extern bool PostMessageW(IntPtr h, uint msg, IntPtr wp, IntPtr lp);
[DllImport("user32.dll")]
public static extern IntPtr GetDlgItem(IntPtr h, int id);
[DllImport("user32.dll")]
public static extern IntPtr SendMessageW(IntPtr h, uint msg, IntPtr wp, IntPtr lp);
'@

function Get-WindowForPid([int]$want) {
    $script:found = [IntPtr]::Zero
    $cb = [W.U2+EnumProc]{
        param($h, $lp)
        $pid2 = 0
        [void][W.U2]::GetWindowThreadProcessId($h, [ref]$pid2)
        if ($pid2 -eq $want) { $script:found = $h; return $false }
        return $true
    }
    [void][W.U2]::EnumWindows($cb, [IntPtr]::Zero)
    return $script:found
}

$outDir = Join-Path $PWD 'x64\Debug'
$mapDir = Join-Path $PWD 'Mapoutput'
Get-Process -Name MapGenerator -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep -Seconds 1

$before = @(Get-ChildItem -Path $mapDir -Filter 'rmg_*.map' | ForEach-Object { $_.Name })
$p = Start-Process -FilePath (Join-Path $outDir 'MapGenerator.exe') -WorkingDirectory $outDir -PassThru
$h = [IntPtr]::Zero
for ($i = 0; $i -lt 20; $i++) {
    Start-Sleep -Milliseconds 500
    $h = Get-WindowForPid $p.Id
    if ($h -ne [IntPtr]::Zero) { break }
}
if ($h -eq [IntPtr]::Zero) { Write-Output 'window not found'; exit 1 }

# environment combo id=110: CB_SETCURSEL(0x014E) -> 0=Archipelago(群岛),
# 1=Continent(大岛屿), 2=TeamContinent(大岛屿群), 3=Inland, 4=Mountainous
$combo = [W.U2]::GetDlgItem($h, 110)
[void][W.U2]::SendMessageW($combo, 0x014E, [IntPtr]$EnvIdx, [IntPtr]::Zero)
Write-Output ('pid=' + $p.Id + ' env=' + $EnvIdx)
[void][W.U2]::PostMessageW($h, 0x0111, [IntPtr]101, [IntPtr]::Zero)

$new = $null
for ($i = 0; $i -lt 300; $i++) {
    Start-Sleep -Seconds 2
    $cur = @(Get-ChildItem -Path $mapDir -Filter 'rmg_*.map' | ForEach-Object { $_.Name })
    $diff = @($cur | Where-Object { $before -notcontains $_ })
    if ($diff.Count -gt 0) { $new = $diff; break }
}
if ($new) { Write-Output ('new map: ' + ($new -join ',')) } else { Write-Output 'no new map' }
Start-Sleep -Seconds 2
[void][W.U2]::PostMessageW($h, 0x0010, [IntPtr]::Zero, [IntPtr]::Zero)
Start-Sleep -Seconds 2
if (-not $p.HasExited) { $p.Kill() }
Write-Output 'done'

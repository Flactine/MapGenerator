param([int]$N = 6, [int]$EnvIdx = 4)
$ErrorActionPreference = 'Continue'
$root = $PWD
for ($i = 1; $i -le $N; $i++) {
    powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $root 'Mapoutput\temp\selfrun_env.ps1') -EnvIdx $EnvIdx | Out-Null
    $f = Get-ChildItem (Join-Path $root 'Mapoutput\rmg_*.map') | Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if ($f) {
        $tag = $f.BaseName
        Copy-Item (Join-Path $root 'Mapoutput\rmg_diag.log') (Join-Path $root ("Mapoutput\temp\rplog_" + $tag + ".txt")) -Force
        Write-Output ("captured " + $f.Name)
    }
}
Write-Output BATCHDONE

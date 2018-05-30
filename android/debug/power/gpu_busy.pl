#
# 监控GPU使用率的脚本
#
#!/usr/bin/perl -w
while(1)
{
    &busy;
    print "\n";
    sleep 1 ;
}
sub busy
{
    $gpu3d = `adb shell cat /sys/class/kgsl/kgsl-3d0/gpubusy`;
    $pct = 0.0;
    if( $gpu3d =~ m/\s*(\d+)\s+(\d+)/)
    {
        if( $1 > 0 && $2 > 0 )
        {
            $pct = $1 / $2 * 100;
        }
        printf("3D GPU Busy: %5.2f\n", $pct);
    }
}

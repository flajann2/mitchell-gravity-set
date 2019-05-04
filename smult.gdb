# file: smult.gdb
# loading: source smult.gdb
# use: nmult 100
# use: smult 100

define smult
    set $step_mult_max = 1000
    if $argc >= 1
        set $step_mult_max = $arg0
    end

    set $step_mult_count = 0
    while ($step_mult_count < $step_mult_max)
        set $step_mult_count = $step_mult_count + 1
        printf "step #%d\n", $step_mult_count
        step
    end
end

define nmult
    set $step_mult_max = 1000
    if $argc >= 1
        set $step_mult_max = $arg0
    end

    set $step_mult_count = 0
    while ($step_mult_count < $step_mult_max)
        set $step_mult_count = $step_mult_count + 1
        printf "next #%d\n", $step_mult_count
        next
    end
end

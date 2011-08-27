function [y, state_ret] = foo(x, u, state, id)
%     y: audio output buffer
% state: state machine with 1024 elements of doubles
%     x: input audio buffer
%     u: value [0,1] of the effect strength knob
%    id: reference to the vital sign being monitored
HR=1; SPO2=2; RR=3; SYSBP=4; DIABP=5; MNBP=6; TEMP=7; ST=8; ETCO2=9; 
FIO2=10; FIAA=11; PPEAK=12; PEEP=13; MVE=14; PCWP=15;

% mcc -B csharedlib:foolib foo.m -C


if (id == HR)
    i1 = 1;
    iend = 512;
    alarm = 0.5*rand(size(x))-0.5;
elseif (id == SPO2)
    i1 = 513;
    iend = 1024;
    alarm = 0.5*sin(2*pi*100*(1:length(x))/44100)';
end

state_ret = state;

if (id ~=HR && id ~=SPO2)
    y=x;
else
    
    for ii = iend:-1:i1+1
        state_ret(ii) = state_ret(ii-1);
    end
    state_ret(i1) = u;   % add newest effect strength value to the beginning

    % if average over 256 frames (256*2560/44100 = ~15 sec) is within 10% of
    % the current nominal value, then add an alarm, otherwise just pass thru
    % the audio
    if (mean(state_ret(i1:i1+256)) > 0.9*u)
        y=x+alarm;
    else
        y=x;
    end
    
end

return;



s = serialport("com3",9600);    
configureTerminator(s,88)
flush(s);

rawOut = ""; %initialize readout variable
hold off;
xlim manual

while (rawOut ~= "END" )
    rawOut = readline(s)
    %if rawOut == "END" 
    %    break
    %end
    procOut = str2double(split(rawOut,"|"))
    [X,Y,Z] = sph2cart(deg2rad(procOut(1)),deg2rad(procOut(2)),procOut(3));
    scatter3(X,Y,Z,4,'b')
    %xlim([-40 0]);         %limit graph if needed
    %zlim([0 40]);
    %ylim([-40 0]);
    axis equal;
    hold on;
end
clear s
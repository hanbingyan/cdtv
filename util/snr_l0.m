function accuracy = snr_l0(noisydata, originaldata)
%  snr: Compute Signal-to-Noise Ratio for images
diff = noisydata-originaldata;
diff = abs(diff);
wrong_number = softl0norm(diff);
accuracy = 1-wrong_number/numel(noisydata);


function [num] = softl0norm(x)
num = sum(sum(sum(abs(x)>20/255)));

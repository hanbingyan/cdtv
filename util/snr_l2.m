function result = snr_l2(noisydata, originaldata)
%  snr: Compute Signal-to-Noise Ratio for images




diff = noisydata-originaldata;
diff = abs(diff);
total = sum(sum(sum(diff.*diff)));

mean_original = mean(mean(mean(originaldata)));
diff2         = originaldata - mean_original;
diff2 = abs(diff2);
total2 = sum(sum(sum(diff2.*diff2)));


ratio = total/ total2;
result = 10 * log10(1/ratio);



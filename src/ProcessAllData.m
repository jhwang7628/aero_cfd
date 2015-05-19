load('log_mocap.mat'); 


listing = dir('./log_*.txt'); 
listing = {listing.name}; 

for ii = 1:numel(listing)
    tmp = load(listing{ii}); 
    nam = listing{ii}; 
    nam = [nam(5:end-4),'.wav']; 
    wavwrite(tmp(:,2)/max(abs(tmp(:,2))), 10000, nam); 
end


% cylinder_nofreq = load('log_cylinder_nofreq.txt'); 
% cylinder_freq = load('log_cylinder_freq.txt'); 
% cylinder_lowalpha = load('log_cylinder_freq_a1.txt'); 

% square_nofreq = load('log_square_nofreq.txt'); 

WRITE=0

listing = dir('*.handData'); 
listing = {listing.name}; 

time = zeros(numel(listing), 1); 
tipPos  = zeros(numel(listing), 3); 
tipVel  = zeros(numel(listing), 3); 
tipSpd  = zeros(numel(listing), 1); 
handDir = zeros(numel(listing), 3); 
palmNor = zeros(numel(listing), 3); 


count = 0; 

N_discret = 10; 
l = linspace(-0.3,0.7,N_discret); 
scale = 3;% random scaling

for ii=1:numel(listing) 
    if (mod(ii,50) == 0)
        fprintf('read # %u\n', ii);
    end

    tmp = dlmread(listing{ii}, '', 1, 0); 
    tipPos(ii,:)  = tmp(1,:)/1000*scale; 
    tipVel(ii,:)  = tmp(2,:)/1000*scale;  
    handDir(ii,:) = tmp(3,:); 
    palmNor(ii,:) = tmp(4,:); 
    tipSpd(ii)  = norm(tipVel(ii,:)); 


    if WRITE % save particle positions
        particles = zeros(N_discret, 3); 
       
        fpath = sprintf('%.5u.particles', count); 
        fp = fopen(fpath,'w'); 
        fprintf(fp, '%u\n', N_discret); 

        for jj=1:N_discret
            particles(jj,:) = tipPos(ii,:) + handDir(ii,:)*l(jj); 
            fprintf(fp, '%.12f %.12f %.12f\n', particles(jj,1), particles(jj,2), particles(jj,3)); 
        end

        fclose(fp);

        % save(fpath, 'particles', '-ascii'); 
    end

    count = count + 1; 

end

t = linspace(0, 0.01*numel(listing), numel(listing));

figure, 
subplot(3,1,1)
plot(t, tipSpd); 
ylabel('Scaled Tip Speed (m/s)'); 
axis tight

subplot(3,1,2)
plot(t, handDir); 
legend('x','y','z');
ylabel('Hand Direction');

subplot(3,1,3)
plot(t, palmNor); 
legend('x','y','z');
ylabel('Palm Normal');
xlabel('Time (s)');



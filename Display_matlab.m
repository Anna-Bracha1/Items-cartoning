clear all;
close all;

numOfBoxes = 6;

filename = 'Boxes.txt';
fileID = fopen(filename','r');

formatSpec = '%d %d %d %d %d %d %d %d %d %d';
sizeBox = [10 10];

Box = zeros(10, 10, numOfBoxes);

for i = 1:numOfBoxes
	Box(:,:,i) = fscanf(fileID, formatSpec, sizeBox);
	Box(:,:,i) = Box(:,:,i)';
end

fclose(fileID);

mymap = colormap(hsv);  
mymap(1,:) = [0 0 0];   %make first color black

figure(1);
colormap(mymap);
for i = 1:numOfBoxes
    subplot(2, 4, i);
    image(Box(:,:,i), 'CDataMapping', 'scaled');
    title(['Box ' num2str(i)]);
    
    stats = regionprops(Box(:,:,i), 'centroid', 'BoundingBox');
    for j = 1:length(stats)
        if(isnan(stats(j).Centroid(1)) == 0)
            text(stats(j).Centroid(1), stats(j).Centroid(2),['\color{black}', num2str(j)]);
            rectangle('Position', stats(j).BoundingBox);
        end
    end
end
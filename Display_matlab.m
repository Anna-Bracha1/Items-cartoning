
formatSpec = '%d %d %d %d %d %d %d %d %d %d';

filename = 'Boxes.txt';
fileID = fopen('Items.txt','r');

formatSpec = '%d %d %d %d %d %d %d %d %d %d';
sizeA = [10 10];

for i = 1:numOfBoxes
	Box(i) = fscanf(fileID, formatSpec, sizeA);
	Box(i) = Box(i)';
end

fclose(fileID);

figure;
for i = 1:numOfBoxes
	subplot(4, 4, i);
	image(Box(i), 'CDataMapping', 'scaled');
end

%B = imresize(A, scale);

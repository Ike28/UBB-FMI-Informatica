clc

fileID = fopen('keywords_spam.txt', 'r');
kspam = textscan(fileID, '%s');
fclose(fileID);
fileID = fopen('keywords_ham.txt', 'r');
kham = textscan(fileID, '%s');
fclose(fileID);

spamcount = numel(kspam{1});
hamcount = numel(kham{1});
pspam = spamcount/(spamcount + hamcount);
pham = hamcount/(spamcount + hamcount);

unique_spam = unique(kspam{1});
unique_ham = unique(kham{1});
unc_s = length(unique_spam);
unc_h = length(unique_ham); 3

callH = sum(strcmp('call', vectorHam{1})==1);
clickH = sum(strcmp('click', vectorHam{1})==1);
foodH = sum(strcmp('food', vectorHam{1})==1);
freeH = sum(strcmp('free', vectorHam{1})==1);
friendH = sum(strcmp('friend', vectorHam{1})==1);
hereH = sum(strcmp('here', vectorHam{1})==1);
homeH = sum(strcmp('home', vectorHam{1})==1);
motherH = sum(strcmp('mother', vectorHam{1})==1);
nowH = sum(strcmp('now', vectorHam{1})==1);
payH = sum(strcmp('pay', vectorHam{1})==1);
sadH = sum(strcmp('sad', vectorHam{1})==1);
thankH = sum(strcmp('thank', vectorHam{1})==1);
todayH = sum(strcmp('today', vectorHam{1})==1);
urgentH = sum(strcmp('urgent', vectorHam{1})==1);

callS = sum(strcmp('call', vectorSpam{1})==1);
clickS = sum(strcmp('click', vectorSpam{1})==1);
foodS = sum(strcmp('food', vectorSpam{1})==1);
freeS = sum(strcmp('free', vectorSpam{1})==1);
friendS = sum(strcmp('friend', vectorSpam{1})==1);
hereS = sum(strcmp('here', vectorSpam{1})==1);
homeS = sum(strcmp('home', vectorSpam{1})==1);
motherS = sum(strcmp('mother', vectorSpam{1})==1);
nowS = sum(strcmp('now', vectorSpam{1})==1);
payS = sum(strcmp('pay', vectorSpam{1})==1);
sadS = sum(strcmp('sad', vectorSpam{1})==1);
thankS = sum(strcmp('thank', vectorSpam{1})==1);
todayS = sum(strcmp('today', vectorSpam{1})==1);
urgentS = sum(strcmp('urgent', vectorSpam{1})==1);


vectorFrecventaHam = [callH;clickH;foodH;freeH;friendH;hereH;homeH;motherH;nowH;payH;sadH;thankH;todayH;urgentH];
vectorFrecventaSpam = [callS;clickS;foodS;freeS;friendS;hereS;homeS;motherS;nowS;payS;sadS;thankS;todayS;urgentS];
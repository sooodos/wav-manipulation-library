## Joint Work with mchara01

## Library for Processing WAV Audio Files

Information about WAV files and their structure can be found here: http://en.wikipedia.org/wiki/WAV

### Available functionalities
Options   Information

-list<br />Meta-information export for a list of .wav audio files

-mono<br />Converts the audio file from stereo (existence of 2 channels) to monophonic (existence of only one channel). 

-mix<br />Mixing of two tracks

-chop<br />Slices an audio file from one given second to another.

-reverse<br />Inverts the data of an audio file.

-similarity<br />Checks the similarity per byte of the given audio files. The similarity test is based on two algorithms: (a) the Euclidean matching technique and (b) Longest Common Subsequence (LCSS) matching.

–encodeText<br />Hides a text file inside a wav audio file.

–decodeText<br />Decrypt / Recover secret text from a WAV audio file

### Usage
Compile: 
`make clean`
`make`
(change PROJ variable name to your project name)

Execute:
`./wavengine <-option> sound1.wav [ sound2.wav sound3.wav ...]`

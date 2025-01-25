---
noteId: "920b1910db6711efb9e18dffbb9d4a3c"
tags: []

---
 
 # PianoHand - Algos

 ## Members
 - **Tristan Brideweser (Lead)**
 -  

 ## Setting up
For now, the music files tested on are located in fall2024/ which include the json files and the PianoFingeringDataset (PIG). The PIG dataset is a labeled dataset of many songs that can be used to validate our model. Further exploration into its usefulness to our project is needed. 

Last semester, we used a modified version of the Viterbi algorithm. We can continue to test and validate this model. An RL model is also being considered and developed, more to come. 

Navigate to `environment.py`. Currently, only the skeleton is available for classes including Hand and Finger, with a tentative Thumb in the works. This will be implemented based on the progress made by Eletronics and Hardware. 

 ## To Do
 - determine reward function for fingers
 - complete the classes needed 
 - validate models on MIDI data
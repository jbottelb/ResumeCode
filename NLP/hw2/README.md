# Natural Language Processing HW2

Please see https://www3.nd.edu/~dchiang/teaching/nlp/2021/hw2.html for instructions.

## Description

This code trains a neural network to translate chinese to english. Click the link
above for a full description of the homework and homework files, as well as the code
I wrote and did not write. Much of the modules (layers, blue) were provided and the
rest templated. 



## Part 1
BLEU score from Backstroke of the West: 0.04585
Trained model at epoch 10:
Loss = 249,670
Train Perplexity: 113.92
Dev Perplexity: 245.48
Model BLEU score: 0.0

Observations:
I did not even realize these were sentences at first.
The sentences are short and do not even look like actual sentences.
They contain mostly just a couple duplicate words with maybe another after,
and there is some nonsenical punctuation. It is so bad it is hard to
even pick out a distinct pattern of how bad it is. Random generated
sentences could actually be better.

## Part 2
Trained model at epoch 10:
Loss = 205,647
Train Perplexity: 49.43
Dev Perplexity: 120.37
Model BLEU score: 0.0 (Did not improve)

Observations:
The translations now sort of could be sentences. However there are a ton of repeated words.
Most sentences lack more than two or three words. There seem to be more contextual words,
such as "fighters" and "master" which are more Star Wars themed.
The most likely words can now be in other positions, which may explain the duplication.

## Part 3
(For part 3, model2.py was copied into translation_RNN.py. Use that file)
The output for this aprt was saved in part3_out.Context

The model was saved as part3.model, and the translation to part3.test.en

The Bleu score for the model was .04979 which beats Backstroke of the West

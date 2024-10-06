# Doctrian AI Repository

## Welcome!

Welcome to the **Doctrian AI** repository! This open-source project invites AI practitioners, enthusiasts, and developers to contribute to a valuable resource for learning and innovation in artificial intelligence.

## Overview of the Neural Network

A neural network mimics the way our brains process information. Each neuron receives inputs from multiple other neurons and generates an output. Neurons are organized into layers, where a signal—termed a **"pulse"**—originates at the input layer, traverses through hidden layers, and is modified at each neuron before reaching the output layer.

### Structure of the Neural Network

1. **Input Layer**: This layer collects information from the environment and initializes values for the pulse.
2. **Hidden Layers**: These intermediate layers process the pulse without directly exposing their outputs.
3. **Output Layer**: This layer presents the final results of the processing, which are collected without further transmission.

## Learning through Backpropagation

To enable learning, the network updates how each neuron influences subsequent pulses after the signal travels from the input to the output layer. This is achieved through **backpropagation**, which calculates the error by comparing the expected output to the actual output.

Neural networks can generalize from their training data, allowing them to produce accurate outputs for previously unseen inputs. This capability makes them ideal for tasks like pattern recognition and gaming AI.

## XOR Neural Network Example

This repository includes C# interfaces designed to represent a neural network. A specific example demonstrates training a neural network to perform an **XOR operation** on two bits, structured with:

- **2 Input Neurons**
- **2 Hidden Neurons**
- **1 Output Neuron**

### Learning Steps

The neural network learning process consists of four essential steps:

1. **Set Input Data**: Initialize the input data in the perception layer.
2. **Pulse**: Activate the network to process the inputs.
3. **Backpropagate**: Calculate and propagate the errors back through the network.
4. **Apply Learning**: Update the weights based on the errors to improve accuracy.

## Get Involved!

Feel free to explore the repository, contribute your ideas, and enhance the project! Together, we can advance our understanding of AI and its applications.

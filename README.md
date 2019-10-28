# Welcome to the Doctrian AI Repository!

### The Repository is open to all and I invite anyone working in the field of AI to contribute to this resource.

## The Neural Network.

Basically, each neuron in our brain accepts input from many other neurons and then provides a resulting output. Each neuron can have multiple inputs and the neurons will be grouped in layers. While processing a signal (we'll call it a "pulse"), the signal will start at the top layer flowing through and being modified by each neuron in that layer. 
Each neuron will modify the strength of the pulse. After the modification has been completed, the "pulse" will travel to the next layer and be modified again.

Now that you have the details, let's take a step back and see how a large number of cells create a "neural net", or a network of neurons. For a neural net to work, we need at least three groupings of neurons. The top layer is used by the neural net to perceive the environment and is often called the "perception" or "input" layer.  

This is where we will set initial values to be passed through the net with the pulse. The bottom later is where the neural net will expose the final output of our pulse. Notice these neurons don't send their signal anywhere. After the pulse travels to this layer, we'll go pick up the values on the output neurons as the final output of our network's processing. 

All the neurons in the middle layer(s) process the pulse as it travels through the net but are not exposed as direct input or output of the net.  This is often called the "hidden" layer.

#### Making the network learn through back propagation.

In order for our neural net to have the ability to learn, after our signal travels from the top of our net to the bottom, we have to update how each neuron will affect the next pulse that travels the network. This is done by a process called back propagation.  Basically we figure out a figure representing the level of error that our network produced. This is arrived at by comparing the expected output of the net to the actual output.

One of the cool things about neural networks is that after they learn through this iterative process and are fully trained, they can calculate output for input they have never encountered before which makes them ideal for pattern recognition and gaming AI.

##### This Repo contains some actual C# interfaces to represent a neural network.

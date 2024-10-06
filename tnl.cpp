/// <summary>
/// Activates each neuron in the layer using the specified neural network context.
/// </summary>
/// <param name="net">The neural network instance used for processing.</param>
public void Pulse(ITriNeuralNet net)  
{  
    // Activate each neuron in the layer
    foreach (ITriNeuron neuron in m_neurons)  
    {  
        neuron.Pulse(this);  
    }  
}

/// <summary>
/// Applies the learning algorithm to each neuron in the layer based on the neural network context.
/// </summary>
/// <param name="net">The neural network instance used for learning.</param>
public void ApplyLearning(ITriNeuralNet net)  
{  
    // Update weights for each neuron in the layer
    foreach (ITriNeuron neuron in m_neurons)  
    {  
        neuron.ApplyLearning(this);  
    }  
}

/// <summary>
/// Applies the sigmoid activation function to the given input value.
/// </summary>
/// <param name="value">The input value to be transformed.</param>
/// <returns>The sigmoid of the input value.</returns>
private static double Sigmoid(double value)  
{  
    return 1.0 / (1.0 + Math.Exp(-value));  
}

/// <summary>
/// Processes the inputs of the neuron layer and updates the output using the sigmoid activation function.
/// </summary>
/// <param name="layer">The layer to which this neuron belongs.</param>
public void Pulse(ITriNeuralLayer layer)  
{  
    lock (this)  
    {  
        // Reset output before processing
        m_output = 0;  

        // Calculate the weighted sum of inputs
        foreach (var item in m_input)  
        {  
            m_output += item.Key.Output * item.Value.Weight;  
        }  

        // Include the bias in the output calculation
        m_output += m_bias.Weight * BiasWeight;  

        // Apply the sigmoid activation function to the total input
        m_output = Sigmoid(m_output);  
    }  
}

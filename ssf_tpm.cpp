private static double Sigmoid(double value)  
{  
      return 1 / (1 + Math.Exp(-value));  
}  

public void Pulse(TriNeuralLayer layer)  
{  
    lock (this)  
    {  
        m_output = 0;  
        foreach (KeyValuePair<TriNeuronSignal, NeuralFactor> item in m_input)  
            m_output += item.Key.Output * item.Value.Weight;  
        m_output += m_bias.Weight * BiasWeight;  
        m_output = Sigmoid(m_output);  
    }  
} 

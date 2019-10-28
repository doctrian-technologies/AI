public void Pulse(TriNeuralNet net)  
{  
    foreach (TriNeuron n in m_neurons)  
        n.Pulse(this);  
}  
public void ApplyLearning(TriNeuralNet net)  
{  
    foreach (TriNeuron n in m_neurons)  
        n.ApplyLearning(this);  
}  

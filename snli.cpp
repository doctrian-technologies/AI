public interface TriNeuralLayer : IList<TriNeuron>  
{  
    void Pulse(TriNeuralNet net);  
    void ApplyLearning(TriNeuralNet net);  
} 

public interface TriNeuron : TriNeuronSignal, TriNeuronReceptor  
{  
    void Pulse(TriNeuralLayer layer);  
   void ApplyLearning(TriNeuralLayer layer);  
    NeuralFactor Bias { get; set; }  
    double BiasWeight { get; set; }  
    double Error { get; set; }  
} 

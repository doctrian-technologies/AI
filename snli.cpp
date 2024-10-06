/// <summary>
/// Represents a layer of tri-neurons in a neural network.
/// </summary>
public interface ITriNeuralLayer : IList<ITriNeuron>  
{  
    /// <summary>
    /// Pulses the layer, processing inputs and updating outputs based on the current state.
    /// </summary>
    /// <param name="net">The neural network associated with this layer.</param>
    void Pulse(ITriNeuralNet net);  

    /// <summary>
    /// Applies learning adjustments based on the errors calculated during training.
    /// </summary>
    /// <param name="net">The neural network associated with this layer.</param>
    void ApplyLearning(ITriNeuralNet net);  
}

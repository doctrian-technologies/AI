/// <summary>
/// Interface representing a triangular neuron that can send and receive signals,
/// as well as participate in learning.
/// </summary>
public interface ITriNeuron : ITriNeuronSignal, ITriNeuronReceptor
{
    /// <summary>
    /// Pulses the neuron, activating it based on the input from the specified layer.
    /// </summary>
    /// <param name="layer">The composite layer that provides input to the neuron.</param>
    void Pulse(ICompositeLayer layer);
    
    /// <summary>
    /// Applies learning adjustments based on the provided layer's data.
    /// </summary>
    /// <param name="layer">The composite layer that contains relevant data for learning.</param>
    void ApplyLearning(ICompositeLayer layer);
    
    /// <summary>
    /// Gets or sets the bias factor for the neuron.
    /// </summary>
    NeuralFactor Bias { get; set; }
    
    /// <summary>
    /// Gets or sets the weight of the bias for the neuron.
    /// </summary>
    double BiasWeight { get; set; }
    
    /// <summary>
    /// Gets or sets the error value for the neuron, used during learning.
    /// </summary>
    double Error { get; set; }
}

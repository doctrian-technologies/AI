/// <summary>
/// Represents a receptor in a tri-neuron system, responsible for handling input signals.
/// </summary>
public interface ITriNeuronReceptor  
{  
    /// <summary>
    /// Gets a read-only dictionary of input signals received by the neuron,
    /// mapping each signal to its associated weight represented by a NeuralFactor.
    /// </summary>
    IReadOnlyDictionary<ITriNeuronSignal, NeuralFactor> Input { get; }  
}

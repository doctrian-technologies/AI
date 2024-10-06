/// <summary>
/// Represents a weight factor in a neural network, including its current value and adjustment (delta).
/// </summary>
public class NeuralFactor  
{  
    #region Constructors  
    /// <summary>
    /// Initializes a new instance of the <see cref="NeuralFactor"/> class with a specified weight.
    /// </summary>
    /// <param name="weight">The initial weight value.</param>
    public NeuralFactor(double weight)  
    {  
        Weight = weight;  
        Delta = 0.0;  
    }  
    #endregion  
 
    #region Properties  
    /// <summary>
    /// Gets or sets the weight of the factor.
    /// </summary>
    public double Weight { get; set; }  

    /// <summary>
    /// Gets or sets the adjustment to the weight (delta).
    /// </summary>
    public double Delta { get; set; }  
    #endregion  

    #region Methods  
    /// <summary>
    /// Applies the current delta to the weight and resets the delta to zero.
    /// </summary>
    public void ApplyDelta()  
    {  
        Weight += Delta;  
        Delta = 0.0;  
    }  
    #endregion  
}

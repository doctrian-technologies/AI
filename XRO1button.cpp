private void button1_Click(object sender, EventArgs e)  
{  
    // Initialize the neural network
    var net = new NeuralNet();  
    const double high = 0.9;  
    const double low = 0.1;  
    const double mid = 0.5;  
    
    // Initialize the neural network with:
    //   2 input neurons,
    //   2 hidden layer neurons,
    //   1 output neuron.
    net.Initialize(1, 2, 2, 1);  
    
    // Input and output data for training (XOR problem)
    double[][] input = 
    {  
        new double[] { high, high },  
        new double[] { low, high },  
        new double[] { high, low },  
        new double[] { low, low }  
    };  
    
    double[][] output = 
    {  
        new double[] { low },  
        new double[] { high },  
        new double[] { high },  
        new double[] { low }  
    };  
    
    int count = 0;  
    
    // Train the network until all outputs are satisfactory
    do  
    {  
        count++;  
        
        // Train the network for 100 iterations
        for (int i = 0; i < 100; i++)  
        {  
            net.Train(input, output);  
        }  
        
        net.ApplyLearning();  

        // Test the network with various input combinations
        TestNetwork(net, low, high, out double ll, out double lh, out double hl, out double hh);  
        
    } while (hh > mid || lh < mid || hl < mid || ll > mid);  
    
    MessageBox.Show($"{count * 100} iterations required for training");  
}

/// <summary>
/// Tests the neural network with specified input values and captures the output.
/// </summary>
/// <param name="net">The neural network to test.</param>
/// <param name="low">The low input value.</param>
/// <param name="high">The high input value.</param>
/// <param name="ll">Output for (low, low).</param>
/// <param name="lh">Output for (low, high).</param>
/// <param name="hl">Output for (high, low).</param>
/// <param name="hh">Output for (high, high).</param>
private void TestNetwork(NeuralNet net, double low, double high, out double ll, out double lh, out double hl, out double hh)  
{  
    // Test (low, low)
    SetInputs(net, low, low);
    ll = GetOutput(net);  

    // Test (high, low)
    SetInputs(net, high, low);
    hl = GetOutput(net);  

    // Test (low, high)
    SetInputs(net, low, high);
    lh = GetOutput(net);  

    // Test (high, high)
    SetInputs(net, high, high);
    hh = GetOutput(net);  
}

/// <summary>
/// Sets the inputs for the neural network.
/// </summary>
/// <param name="net">The neural network.</param>
/// <param name="input1">First input value.</param>
/// <param name="input2">Second input value.</param>
private void SetInputs(NeuralNet net, double input1, double input2)
{
    net.PerceptionLayer[0].Output = input1;  
    net.PerceptionLayer[1].Output = input2;  
    net.Pulse();  
}

/// <summary>
/// Retrieves the output from the output layer of the neural network.
/// </summary>
/// <param name="net">The neural network.</param>
/// <returns>The output value from the output layer.</returns>
private double GetOutput(NeuralNet net)
{
    return net.OutputLayer[0].Output;  
}

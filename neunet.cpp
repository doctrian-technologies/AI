public void Initialize(int randomSeed, int inputNeuronCount, int hiddenNeuronCount, int outputNeuronCount)  
{  
    int i, j, k, layerCount;  
    Random rand;  
    TriNeuralLayer layer;  
    // initializations  
    rand = new Random(randomSeed);  
    m_inputLayer = new NeuralLayer();  
    m_outputLayer = new NeuralLayer();  
    m_hiddenLayer = new NeuralLayer();  
    for (i = 0; i < inputNeuronCount; i++)  
        m_inputLayer.Add(new Neuron());  
    for (i = 0; i < outputNeuronCount; i++)  
        m_outputLayer.Add(new Neuron());  
    for (i = 0; i < hiddenNeuronCount; i++)  
        m_hiddenLayer.Add(new Neuron());  
    // wire-up input layer to hidden layer  
    for (i = 0; i < m_hiddenLayer.Count; i++)  
        for (j = 0; j < m_inputLayer.Count; j++)  
            m_hiddenLayer[i].Input.Add(m_inputLayer[j],  
                 new NeuralFactor( rand.NextDouble()));  
    // wire-up output layer to hidden layer  
    for (i = 0; i < m_outputLayer.Count; i++)  
        for (j = 0; j < m_hiddenLayer.Count; j++)  
            m_outputLayer[i].Input.Add(HiddenLayer[j],  
                 new NeuralFactor(rand.NextDouble()));  

    public void Pulse()  
{  
    lock (this)  
    {  
        m_hiddenLayer.Pulse(this);  
        m_outputLayer.Pulse(this);  
    }  
}  
public void ApplyLearning()  
{  
    lock (this)  
    {  
        m_hiddenLayer.ApplyLearning(this);  
        m_outputLayer.ApplyLearning(this);  
    }  
}  
    private void BackPropogation(double[] desiredResults)  
{  
    int i, j;  
    double temp, error;  
    TriNeuron outputNode, inputNode, hiddenNode, node, node2;  
    // Calcualte output error values  
    for (i = 0; i < m_outputLayer.Count; i++)  
    {  
        temp = m_outputLayer[i].Output;  
        m_outputLayer[i].Error = (desiredResults[i] - temp) * temp * (1.0F - temp);  
    }  
    // calculate hidden layer error values  
    for (i = 0; i < m_hiddenLayer.Count; i++)  
    {  
        node = m_hiddenLayer[i];  
        error = 0;  
        for (j = 0; j < m_outputLayer.Count; j++)  
        {  
            outputNode = m_outputLayer[j];  
            error += outputNode.Error * outputNode.Input[node].Weight * node.Output * (1.0 - node.Output);  
        }  
        node.Error = error;  
    }  
    // adjust output layer weight change  
    for (i = 0; i < m_hiddenLayer.Count; i++)  
    {  
        node = m_hiddenLayer[i];  
        for (j = 0; j < m_outputLayer.Count; j++)  
        {  
            outputNode = m_outputLayer[j];  
            outputNode.Input[node].Weight += m_learningRate * m_outputLayer[j].Error * node.Output;  
            outputNode.Bias.Delta += m_learningRate * m_outputLayer[j].Error * outputNode.Bias.Weight;  
        }  
    }  
    // adjust hidden layer weight change  
    for (i = 0; i < m_inputLayer.Count; i++)  
    {  
        inputNode = m_inputLayer[i];  
        for (j = 0; j < m_hiddenLayer.Count; j++)  
        {  
            hiddenNode = m_hiddenLayer[j];  
            hiddenNode.Input[inputNode].Weight += m_learningRate * hiddenNode.Error * inputNode.Output;  
            hiddenNode.Bias.Delta += m_learningRate * hiddenNode.Error * inputNode.Bias.Weight;  
        }  
    }  
}  

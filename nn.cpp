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

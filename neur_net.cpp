using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

// Activation function interface
public interface IActivationFunction
{
    double Activate(double input);
    double Derivative(double output);
}

// Loss function interface
public interface ILossFunction
{
    double Compute(double[] predicted, double[] actual);
    double[] Derivative(double[] predicted, double[] actual);
}

// Neuron interface
public interface INeuron
{
    double Output { get; set; }
    double Error { get; set; }
    Dictionary<INeuron, NeuralFactor> Input { get; }
    Bias Bias { get; }
    void Activate(IActivationFunction activationFunction);
}

// Neural Factor class (represents weights)
public class NeuralFactor
{
    public double Weight { get; set; }
    public NeuralFactor(double weight) => Weight = weight;
}

// Bias class
public class Bias
{
    public double Weight { get; set; }
    public double Delta { get; set; }
    public Bias() { Weight = 0.0; Delta = 0.0; }
}

// Neuron implementation
public class Neuron : INeuron
{
    public double Output { get; set; }
    public double Error { get; set; }
    public Dictionary<INeuron, NeuralFactor> Input { get; private set; }
    public Bias Bias { get; private set; }

    public Neuron()
    {
        Input = new Dictionary<INeuron, NeuralFactor>();
        Bias = new Bias();
    }

    public void Activate(IActivationFunction activationFunction)
    {
        double sum = Input.Sum(x => x.Key.Output * x.Value.Weight) + Bias.Weight;
        Output = activationFunction.Activate(sum);
    }
}

// Layer interface
public interface ILayer
{
    void Add(INeuron neuron);
    void Pulse(IActivationFunction activationFunction);
    void ApplyLearning(double learningRate);
    int Count { get; }
    IEnumerable<INeuron> Neurons { get; }
}

// Composite layer implementation
public class CompositeLayer : ILayer
{
    private List<INeuron> neurons = new List<INeuron>();
    
    public void Add(INeuron neuron) => neurons.Add(neuron);

    public void Pulse(IActivationFunction activationFunction) => 
        Parallel.ForEach(neurons, neuron => neuron.Activate(activationFunction));
    
    public void ApplyLearning(double learningRate) 
    { 
        // Implement learning logic here 
    }

    public int Count => neurons.Count;
    public IEnumerable<INeuron> Neurons => neurons;
}

// Neural network class
public class NeuralNetwork
{
    private CompositeLayer m_inputLayer;
    private CompositeLayer m_hiddenLayer;
    private CompositeLayer m_outputLayer;
    private Random rand;

    public double LearningRate { get; set; } = 0.01;

    public NeuralNetwork(int inputNeuronCount, int hiddenNeuronCount, int outputNeuronCount, int randomSeed)
    {
        rand = new Random(randomSeed);
        m_inputLayer = new CompositeLayer();
        m_hiddenLayer = new CompositeLayer();
        m_outputLayer = new CompositeLayer();

        InitializeLayers(inputNeuronCount, hiddenNeuronCount, outputNeuronCount);
        WireLayers();
    }

    private void InitializeLayers(int inputCount, int hiddenCount, int outputCount)
    {
        for (int i = 0; i < inputCount; i++)
            m_inputLayer.Add(new Neuron());

        for (int i = 0; i < hiddenCount; i++)
            m_hiddenLayer.Add(new Neuron());

        for (int i = 0; i < outputCount; i++)
            m_outputLayer.Add(new Neuron());
    }

    private void WireLayers()
    {
        WireInputToHidden();
        WireHiddenToOutput();
    }

    private void WireInputToHidden()
    {
        foreach (var hidden in m_hiddenLayer.Neurons)
            foreach (var input in m_inputLayer.Neurons)
                hidden.Input.Add(input, new NeuralFactor(rand.NextDouble()));
    }

    private void WireHiddenToOutput()
    {
        foreach (var output in m_outputLayer.Neurons)
            foreach (var hidden in m_hiddenLayer.Neurons)
                output.Input.Add(hidden, new NeuralFactor(rand.NextDouble()));
    }

    public void Train(double[][] inputs, double[][] expected, int batchSize)
    {
        for (int i = 0; i < inputs.Length; i += batchSize)
        {
            var miniBatch = inputs.Skip(i).Take(batchSize).ToArray();
            var miniExpected = expected.Skip(i).Take(batchSize).ToArray();
            TrainMiniBatch(miniBatch, miniExpected);
        }
    }

    private void TrainMiniBatch(double[][] inputs, double[][] expected)
    {
        for (int i = 0; i < inputs.Length; i++)
        {
            SetInput(inputs[i]);
            Pulse(new SigmoidActivationFunction());
            BackPropagation(expected[i]);
        }
    }

    private void SetInput(double[] input)
    {
        for (int i = 0; i < m_inputLayer.Count; i++)
            (m_inputLayer.Neurons.ElementAt(i) as Neuron).Output = input[i];
    }

    private void Pulse(IActivationFunction activationFunction)
    {
        m_hiddenLayer.Pulse(activationFunction);
        m_outputLayer.Pulse(activationFunction);
    }

    private void BackPropagation(double[] desiredResults)
    {
        CalculateOutputErrors(desiredResults);
        CalculateHiddenErrors();
        UpdateWeights();
    }

    private void CalculateOutputErrors(double[] desiredResults)
    {
        for (int i = 0; i < m_outputLayer.Count; i++)
        {
            var outputNeuron = m_outputLayer.Neurons.ElementAt(i) as Neuron;
            outputNeuron.Error = (desiredResults[i] - outputNeuron.Output) * outputNeuron.Output * (1.0 - outputNeuron.Output);
        }
    }

    private void CalculateHiddenErrors()
    {
        for (int i = 0; i < m_hiddenLayer.Count; i++)
        {
            var hiddenNeuron = m_hiddenLayer.Neurons.ElementAt(i) as Neuron;
            hiddenNeuron.Error = m_outputLayer.Neurons.Sum(outputNeuron =>
                outputNeuron.Error * outputNeuron.Input[hiddenNeuron].Weight * hiddenNeuron.Output * (1.0 - hiddenNeuron.Output));
        }
    }

    private void UpdateWeights()
    {
        UpdateOutputWeights();
        UpdateHiddenWeights();
    }

    private void UpdateOutputWeights()
    {
        for (int i = 0; i < m_hiddenLayer.Count; i++)
        {
            var hiddenNeuron = m_hiddenLayer.Neurons.ElementAt(i) as Neuron;
            for (int j = 0; j < m_outputLayer.Count; j++)
            {
                var outputNeuron = m_outputLayer.Neurons.ElementAt(j) as Neuron;
                outputNeuron.Input[hiddenNeuron].Weight += LearningRate * outputNeuron.Error * hiddenNeuron.Output;
            }
        }
    }

    private void UpdateHiddenWeights()
    {
        for (int i = 0; i < m_inputLayer.Count; i++)
        {
            var inputNeuron = m_inputLayer.Neurons.ElementAt(i) as Neuron;
            for (int j = 0; j < m_hiddenLayer.Count; j++)
            {
                var hiddenNeuron = m_hiddenLayer.Neurons.ElementAt(j) as Neuron;
                hiddenNeuron.Input[inputNeuron].Weight += LearningRate * hiddenNeuron.Error * inputNeuron.Output;
            }
        }
    }
}

// Example activation function
public class SigmoidActivationFunction : IActivationFunction
{
    public double Activate(double input) => 1.0 / (1.0 + Math.Exp(-input));
    public double Derivative(double output) => output * (1.0 - output);
}

// Example loss function
public class MeanSquaredError : ILossFunction
{
    public double Compute(double[] predicted, double[] actual) =>
        predicted.Zip(actual, (p, a) => Math.Pow(p - a, 2)).Average();

    public double[] Derivative(double[] predicted, double[] actual)
    {
        return predicted.Zip(actual, (p, a) => p - a).ToArray();
    }
}

// Usage example
public class Program
{
    public static void Main()
    {
        int inputCount = 2;
        int hiddenCount = 3;
        int outputCount = 1;
        int seed = 42;

        var nn = new NeuralNetwork(inputCount, hiddenCount, outputCount, seed);

        // Training data (XOR problem)
        double[][] inputs = 
        {
            new double[] { 0, 0 },
            new double[] { 0, 1 },
            new double[] { 1, 0 },
            new double[] { 1, 1 }
        };

        double[][] expected = 
        {
            new double[] { 0 },
            new double[] { 1 },
            new double[] { 1 },
            new double[] { 0 }
        };

        nn.Train(inputs, expected, batchSize: 2);
        
        // Test after training
        foreach (var input in inputs)
        {
            nn.SetInput(input);
            nn.Pulse(new SigmoidActivationFunction());
            Console.WriteLine($"Input: {string.Join(", ", input)} | Output: {nn.m_outputLayer.Neurons.First().Output}");
        }
    }
}

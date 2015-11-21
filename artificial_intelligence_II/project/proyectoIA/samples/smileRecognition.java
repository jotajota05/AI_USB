package samples;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.Vector;

import neuralj.datasets.Pattern;
import neuralj.datasets.PatternSet;
import neuralj.networks.feedforward.FeedForwardNeuralNetwork;
import neuralj.networks.feedforward.learning.FeedForwardNetworkLearningAlgorithm.LearningStrategy;
import neuralj.networks.feedforward.learning.bprop.BackPropagation;
import neuralj.watchers.ConsoleWatcher;

public class smileRecognition {
	public static void main(String[] args) throws InterruptedException
	{
		// Create the pattern set
		PatternSet pattern_set = new PatternSet();
		// Define the token to split the pattern items by
		Pattern.split_token = " ";
		// Add the XOR table items
		
		try{	
			// Open the file that is the first 
			// command line parameter
			FileInputStream fstream1 = new FileInputStream("inputs_imagenes.txt");
			FileInputStream fstream2 = new FileInputStream("inputs_targets.txt");
			// Get the object of DataInputStream
			DataInputStream in1 = new DataInputStream(fstream1);
			DataInputStream in2 = new DataInputStream(fstream2);
			BufferedReader br1 = new BufferedReader(new InputStreamReader(in1));
			BufferedReader br2 = new BufferedReader(new InputStreamReader(in2));
			String current_input, current_target;
			//Read File Line By Line
			while ((current_input = br1.readLine()) != null && (current_target = br2.readLine()) != null)   {
				// Print the content on the console
				//System.out.print(current_input);
				//System.out.print(" ");
				//System.out.println(current_target);
				pattern_set.addPattern(new Pattern(current_input, current_target));
			}
			//Close 	the input stream
			in1.close();
			in2.close();
		}catch (Exception e){//Catch exception if any
			System.err.println("Error: " + e.getMessage());
		}
		// Initialize the network by giving it's input neurons, hidden neurons
		// and output neurons
		FeedForwardNeuralNetwork net = new FeedForwardNeuralNetwork(480, new int[] { 10 , 10 }, 1);
		// Initialize the BackPropagation algorithm
		BackPropagation bp = new BackPropagation(net);
		// Specify the pattern set that's going to be used for training
		bp.pattern_set = pattern_set;
		// Specify the learning method (Memorize,Generalize)
		bp.learning_strategy = LearningStrategy.Memorize;
		// Specify the desired error (the lower the error, the more accurate the
		// results)
		bp.desired_error = 0.001;
		// Specify the maximum number of epochs the training may take
		bp.maximum_epochs = 1000000000;
		// Attach a ConsoleWatcher to be able to monitor the training in the
		// console
		bp.watcher = new ConsoleWatcher(bp);
		// Since we are going to want to wait for the end of the training
		// thread,
		// we have to specify in advance that the training is undergoing,
		// otherwise,
		// the testing would take place before the start of the training
		bp.is_running = true;
		// Start the training
		bp.start();
		// Wait for the training to finish (sleeping for 1 second every pass to
		// save CPU time)
		while (bp.is_running)
			Thread.sleep(1000);
		// Test the network's accuracy
		//new ConsoleTester(bp.network).test(pattern_set);
		Vector<Double> input_test = new Vector<Double>();
		Vector<Double> out_test;
		try{	
			// Open the file that is the first 
			// command line parameter
			FileInputStream fstream = new FileInputStream("out_imagenes.txt");
			// Get the object of DataInputStream
			DataInputStream in = new DataInputStream(fstream);
			BufferedReader br = new BufferedReader(new InputStreamReader(in));
			String current_test;
			String[] tok;
			int num = 0;
			//Read File Line By Line
			while ((current_test = br.readLine()) != null )   {
				num++;
				// Print the content on the console
				tok = current_test.split("\\b\\s");
				for(int i = 0;i < tok.length;i++) {
					input_test.add(Double.valueOf(tok[i]).doubleValue());
				}
				//System.out.println("Input_test = "+input_test);
				out_test = net.feedForward(input_test);
				System.out.print("Out "+num+" = ");
				System.out.println(out_test);
				input_test.clear();
			}
			//Close 	the input stream
			in.close();
		}catch (Exception e){//Catch exception if any
			System.err.println("Error: " + e.getMessage());
		}
	}
}

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <iomanip> // For std::fixed and std::setprecision
#include <limits>  // For std::numeric_limits

// Constants for the neural network architecture
constexpr int INPUT_SIZE = 28 * 28;    // 28x28 pixel images
constexpr int HIDDEN_SIZE = 128;       // Size of hidden layer
constexpr int OUTPUT_SIZE = 10;        // 10 output classes (0-9)
constexpr double LEARNING_RATE = 0.01; // Learning rate for gradient descent (adjusted for stability with synthetic data)
constexpr int MAX_EPOCHS = 50;         // Maximum training epochs (increased for better synthetic data learning)
constexpr int BATCH_SIZE = 10;         // Batch size for training

// Structure to represent an image and its label
struct DigitImage
{
    std::vector<double> pixels;
    int label;
};

// Helper functions for neural network operations
namespace NNUtils
{
    // Activation function: sigmoid
    double sigmoid(double x)
    {
        return 1.0 / (1.0 + exp(-x));
    }

    // Derivative of sigmoid function
    double sigmoid_derivative(double x)
    {
        double sigmoid_x = sigmoid(x);
        return sigmoid_x * (1.0 - sigmoid_x);
    }

    // Apply sigmoid to a whole vector
    std::vector<double> sigmoid_vector(const std::vector<double> &vec)
    {
        std::vector<double> result(vec.size());
        for (size_t i = 0; i < vec.size(); ++i)
        {
            result[i] = sigmoid(vec[i]);
        }
        return result;
    }

    // ReLU activation function
    double relu(double x)
    {
        return std::max(0.0, x);
    }

    // Derivative of ReLU
    double relu_derivative(double x)
    {
        return x > 0 ? 1.0 : 0.0;
    }

    // Softmax function for output layer
    std::vector<double> softmax(const std::vector<double> &vec)
    {
        std::vector<double> result(vec.size());
        double max_val = 0;
        if (!vec.empty())
        { // Ensure vec is not empty
            max_val = *std::max_element(vec.begin(), vec.end());
        }
        else
        {
            return result; // Return empty result for empty input
        }

        double sum = 0.0;

        // Compute exp(x_i - max) for numerical stability
        for (size_t i = 0; i < vec.size(); ++i)
        {
            result[i] = exp(vec[i] - max_val);
            sum += result[i];
        }

        // Normalize
        if (sum == 0)
        { // Avoid division by zero
            // If sum is zero (e.g., all elements were very small negative after subtracting max_val)
            // we can either return a uniform distribution or handle as an error.
            // For now, let's assign 1/N to each element if possible.
            if (!result.empty())
            {
                double val = 1.0 / result.size();
                for (size_t i = 0; i < vec.size(); ++i)
                {
                    result[i] = val;
                }
            }
            return result;
        }

        for (size_t i = 0; i < vec.size(); ++i)
        {
            result[i] /= sum;
        }

        return result;
    }

    // Matrix-vector multiplication (weights * inputs + bias)
    std::vector<double> matrix_vector_multiply(const std::vector<std::vector<double>> &matrix,
                                               const std::vector<double> &vec,
                                               const std::vector<double> &bias)
    {
        if (matrix.empty() || vec.empty() || matrix[0].size() != vec.size() || matrix.size() != bias.size())
        {
            // Handle dimension mismatch or empty inputs
            // This could throw an error or return an empty vector
            std::cerr << "Error: Matrix-vector multiplication dimension mismatch or empty inputs." << std::endl;
            if (!matrix.empty())
                return std::vector<double>(matrix.size(), 0.0);
            return {};
        }
        std::vector<double> result(matrix.size(), 0.0);
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            for (size_t j = 0; j < vec.size(); ++j)
            {
                result[i] += matrix[i][j] * vec[j];
            }
            result[i] += bias[i];
        }
        return result;
    }

    // Create one-hot encoded target vector
    std::vector<double> one_hot_encode(int label, int size)
    {
        std::vector<double> result(size, 0.0);
        if (label >= 0 && label < size)
        {
            result[label] = 1.0;
        }
        return result;
    }

    // Random initialization with Xavier/Glorot initialization
    double init_weight(int fan_in, int fan_out)
    {
        double limit = sqrt(6.0 / (fan_in + fan_out));
        static std::random_device rd;
        static std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<double> dis(-limit, limit);
        return dis(gen);
    }
}

// Neural Network class
class NeuralNetwork
{
private:
    // Weights and biases
    std::vector<std::vector<double>> weights_input_hidden;
    std::vector<double> bias_hidden;
    std::vector<std::vector<double>> weights_hidden_output;
    std::vector<double> bias_output;

    // Cached values for backpropagation
    std::vector<double> input_layer;
    std::vector<double> hidden_layer_z; // Pre-activation
    std::vector<double> hidden_layer;   // Post-activation
    std::vector<double> output_layer_z; // Pre-activation
    std::vector<double> output_layer;   // Post-activation

public:
    NeuralNetwork()
    {
        // Initialize weights and biases with random values
        initialize_weights();
    }

    void initialize_weights()
    {
        // Initialize weights for input -> hidden layer
        weights_input_hidden.resize(HIDDEN_SIZE, std::vector<double>(INPUT_SIZE));
        for (int i = 0; i < HIDDEN_SIZE; ++i)
        {
            for (int j = 0; j < INPUT_SIZE; ++j)
            {
                weights_input_hidden[i][j] = NNUtils::init_weight(INPUT_SIZE, HIDDEN_SIZE);
            }
        }

        // Initialize biases for hidden layer
        bias_hidden.resize(HIDDEN_SIZE);
        for (int i = 0; i < HIDDEN_SIZE; ++i)
        {
            // Biases are often initialized to zero or small constants,
            // but using init_weight like other weights is also a common strategy.
            bias_hidden[i] = 0.0; // NNUtils::init_weight(INPUT_SIZE, HIDDEN_SIZE); // Or simply 0.0
        }

        // Initialize weights for hidden -> output layer
        weights_hidden_output.resize(OUTPUT_SIZE, std::vector<double>(HIDDEN_SIZE));
        for (int i = 0; i < OUTPUT_SIZE; ++i)
        {
            for (int j = 0; j < HIDDEN_SIZE; ++j)
            {
                weights_hidden_output[i][j] = NNUtils::init_weight(HIDDEN_SIZE, OUTPUT_SIZE);
            }
        }

        // Initialize biases for output layer
        bias_output.resize(OUTPUT_SIZE);
        for (int i = 0; i < OUTPUT_SIZE; ++i)
        {
            bias_output[i] = 0.0; // NNUtils::init_weight(HIDDEN_SIZE, OUTPUT_SIZE); // Or simply 0.0
        }
    }

    // Forward pass through the network
    std::vector<double> forward(const std::vector<double> &inputs)
    {
        if (inputs.size() != INPUT_SIZE)
        {
            std::cerr << "Error: Input size mismatch in forward pass." << std::endl;
            return {}; // Return empty vector on error
        }
        // Store input for backpropagation
        input_layer = inputs;

        // Hidden layer calculation (with ReLU activation)
        hidden_layer_z = NNUtils::matrix_vector_multiply(weights_input_hidden, inputs, bias_hidden);
        hidden_layer.resize(hidden_layer_z.size());
        for (size_t i = 0; i < hidden_layer_z.size(); ++i)
        {
            hidden_layer[i] = NNUtils::relu(hidden_layer_z[i]);
        }

        // Output layer calculation (with softmax activation)
        output_layer_z = NNUtils::matrix_vector_multiply(weights_hidden_output, hidden_layer, bias_output);
        output_layer = NNUtils::softmax(output_layer_z);

        return output_layer;
    }

    // Back propagation
    void back_propagation(const std::vector<double> &target)
    {
        if (target.size() != OUTPUT_SIZE)
        {
            std::cerr << "Error: Target size mismatch in backpropagation." << std::endl;
            return;
        }
        if (output_layer.size() != OUTPUT_SIZE || hidden_layer.size() != HIDDEN_SIZE || input_layer.size() != INPUT_SIZE)
        {
            std::cerr << "Error: Layer sizes not initialized correctly before backpropagation." << std::endl;
            return;
        }

        // Output layer error (delta for softmax with cross-entropy is typically (output - target))
        std::vector<double> output_delta(OUTPUT_SIZE);
        for (int i = 0; i < OUTPUT_SIZE; ++i)
        {
            output_delta[i] = output_layer[i] - target[i];
        }

        // Hidden layer error
        std::vector<double> hidden_delta(HIDDEN_SIZE, 0.0);
        for (int i = 0; i < HIDDEN_SIZE; ++i)
        {
            double error_sum = 0.0;
            for (int j = 0; j < OUTPUT_SIZE; ++j)
            {
                error_sum += output_delta[j] * weights_hidden_output[j][i];
            }
            hidden_delta[i] = error_sum * NNUtils::relu_derivative(hidden_layer_z[i]);
        }

        // Update weights and biases for hidden -> output
        for (int i = 0; i < OUTPUT_SIZE; ++i)
        {
            for (int j = 0; j < HIDDEN_SIZE; ++j)
            {
                weights_hidden_output[i][j] -= LEARNING_RATE * output_delta[i] * hidden_layer[j];
            }
            bias_output[i] -= LEARNING_RATE * output_delta[i];
        }

        // Update weights and biases for input -> hidden
        for (int i = 0; i < HIDDEN_SIZE; ++i)
        {
            for (int j = 0; j < INPUT_SIZE; ++j)
            {
                // Ensure input_layer[j] is valid
                if (j < input_layer.size())
                {
                    weights_input_hidden[i][j] -= LEARNING_RATE * hidden_delta[i] * input_layer[j];
                }
                else
                {
                    std::cerr << "Warning: input_layer access out of bounds during weight update." << std::endl;
                }
            }
            bias_hidden[i] -= LEARNING_RATE * hidden_delta[i];
        }
    }

    // Train the network on a single example
    void train_single(const std::vector<double> &inputs, const std::vector<double> &targets)
    {
        forward(inputs);
        if (!output_layer.empty())
        { // Proceed only if forward pass was successful
            back_propagation(targets);
        }
    }

    // Predict the digit for an input image
    int predict(const std::vector<double> &inputs)
    {
        if (inputs.empty())
            return -1; // Invalid input
        std::vector<double> outputs = forward(inputs);
        if (outputs.empty())
            return -1; // Error in forward pass
        return std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end()));
    }

    // Train on a batch of examples (actually processes them one by one, true batching would accumulate gradients)
    void train_batch(const std::vector<DigitImage> &batch)
    {
        for (const auto &example : batch)
        {
            std::vector<double> targets = NNUtils::one_hot_encode(example.label, OUTPUT_SIZE);
            train_single(example.pixels, targets);
        }
    }

    // Calculate accuracy on a dataset
    double evaluate(const std::vector<DigitImage> &dataset)
    {
        if (dataset.empty())
            return 0.0;
        int correct = 0;
        for (const auto &example : dataset)
        {
            int predicted = predict(example.pixels);
            if (predicted == example.label)
            {
                correct++;
            }
        }
        return static_cast<double>(correct) / dataset.size();
    }

    // Save the model weights to a file
    void save_model(const std::string &filename)
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file)
        {
            std::cerr << "Error: Could not open file for saving model: " << filename << std::endl;
            return;
        }

        auto write_vector = [&](const auto &vec)
        {
            for (const auto &val : vec)
            {
                file.write(reinterpret_cast<const char *>(&val), sizeof(val));
            }
        };

        auto write_matrix = [&](const auto &matrix)
        {
            for (const auto &row : matrix)
            {
                write_vector(row);
            }
        };

        // Save hidden layer weights
        write_matrix(weights_input_hidden);
        write_vector(bias_hidden);
        write_matrix(weights_hidden_output);
        write_vector(bias_output);

        file.close();
        std::cout << "Model saved to " << filename << std::endl;
    }

    // Load model weights from a file
    void load_model(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::binary);

        if (!file)
        {
            std::cerr << "Failed to open model file: " << filename << std::endl;
            std::cout << "Initializing with new random weights instead." << std::endl;
            initialize_weights(); // Initialize with random if file not found
            return;
        }

        auto read_vector = [&](auto &vec)
        {
            for (auto &val : vec)
            {
                file.read(reinterpret_cast<char *>(&val), sizeof(val));
            }
        };

        auto read_matrix = [&](auto &matrix)
        {
            for (auto &row : matrix)
            {
                read_vector(row);
            }
        };

        // Ensure vectors are sized correctly before reading
        weights_input_hidden.resize(HIDDEN_SIZE, std::vector<double>(INPUT_SIZE));
        bias_hidden.resize(HIDDEN_SIZE);
        weights_hidden_output.resize(OUTPUT_SIZE, std::vector<double>(HIDDEN_SIZE));
        bias_output.resize(OUTPUT_SIZE);

        read_matrix(weights_input_hidden);
        read_vector(bias_hidden);
        read_matrix(weights_hidden_output);
        read_vector(bias_output);

        if (file.gcount() == 0 && !file.eof())
        { // Check if read failed before EOF
            std::cerr << "Error reading model file or file is corrupted: " << filename << std::endl;
            std::cout << "Initializing with new random weights instead." << std::endl;
            initialize_weights(); // Re-initialize if read error
        }
        else
        {
            std::cout << "Model loaded from " << filename << std::endl;
        }
        file.close();
    }
};

// Image preprocessing functions
namespace ImagePreprocessing
{
    // Center the digit in the image
    std::vector<double> center_digit(const std::vector<double> &image, int width, int height)
    {
        int min_x = width, max_x = 0, min_y = height, max_y = 0;
        bool found_pixel = false;

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (image[y * width + x] > 0.1)
                { // Threshold to determine if pixel is part of digit
                    min_x = std::min(min_x, x);
                    max_x = std::max(max_x, x);
                    min_y = std::min(min_y, y);
                    max_y = std::max(max_y, y);
                    found_pixel = true;
                }
            }
        }

        if (!found_pixel)
        {
            return image; // If no digit found, return original image
        }

        int digit_width = max_x - min_x + 1;
        int digit_height = max_y - min_y + 1;
        int center_x_digit = min_x + digit_width / 2;
        int center_y_digit = min_y + digit_height / 2;

        int shift_x = width / 2 - center_x_digit;
        int shift_y = height / 2 - center_y_digit;

        std::vector<double> centered_image(width * height, 0.0);

        for (int y_orig = 0; y_orig < height; ++y_orig)
        {
            for (int x_orig = 0; x_orig < width; ++x_orig)
            {
                int new_x = x_orig + shift_x;
                int new_y = y_orig + shift_y;

                if (image[y_orig * width + x_orig] > 0.1)
                { // Consider only digit pixels for shifting
                    if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height)
                    {
                        centered_image[new_y * width + new_x] = image[y_orig * width + x_orig];
                    }
                }
            }
        }
        return centered_image;
    }

    // Normalize the image values to be between 0 and 1
    std::vector<double> normalize(const std::vector<double> &image)
    {
        std::vector<double> normalized(image.size());
        if (image.empty())
            return normalized;

        double max_val = 0.0;
        for (double pix : image)
        {
            if (pix > max_val)
                max_val = pix;
        }

        if (max_val > 0)
        {
            for (size_t i = 0; i < image.size(); ++i)
            {
                normalized[i] = image[i] / max_val;
            }
        }
        else
        {
            return image; // If image is all zeros, return as is
        }
        return normalized;
    }

    // Preprocess an image before passing it to the neural network
    std::vector<double> preprocess(const std::vector<double> &image, int width, int height)
    {
        if (image.size() != static_cast<size_t>(width * height))
        {
            std::cerr << "Error: Image size does not match width*height in preprocess." << std::endl;
            return {};
        }
        std::vector<double> centered = center_digit(image, width, height);
        std::vector<double> normalized = normalize(centered); // Normalization should happen after centering
        return normalized;
    }
}

// Dummy data loader for demo purposes
class DataLoader
{
public:
    // Generate some synthetic data for demonstration
    static std::vector<DigitImage> generate_synthetic_data(int num_samples)
    {
        std::vector<DigitImage> dataset;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> label_dis(0, 9);
        std::normal_distribution<> noise_dis(0.0, 0.05); // Reduced noise for better learning

        std::vector<std::vector<double>> templates = create_digit_templates();

        for (int i = 0; i < num_samples; ++i)
        {
            int label = label_dis(gen);
            std::vector<double> pixels = templates[label];

            // Add random noise
            for (double &pixel : pixels)
            {
                pixel += noise_dis(gen);
                pixel = std::max(0.0, std::min(1.0, pixel)); // Clamp to [0, 1]
            }

            // Apply preprocessing (centering and normalization)
            // For synthetic templates, they are already somewhat centered.
            // Normalization is good.
            pixels = ImagePreprocessing::normalize(pixels);
            // Centering might be skipped if templates are designed to be centered.
            // For this example, let's apply the full preprocess pipeline.
            // pixels = ImagePreprocessing::preprocess(pixels, 28, 28); // Full preprocess

            dataset.push_back({pixels, label});
        }
        return dataset;
    }

    // Load MNIST dataset from file (simplified version)
    static std::vector<DigitImage> load_mnist(const std::string &images_file, const std::string &labels_file, int max_samples = -1)
    {
        std::vector<DigitImage> dataset;
        std::cout << "Loading MNIST dataset from " << images_file << " and " << labels_file << std::endl;
        std::cout << "This is just a placeholder. In a real application, you would load actual MNIST data." << std::endl;
        std::cout << "Using synthetic data instead for this demo." << std::endl;

        dataset = generate_synthetic_data(max_samples > 0 ? max_samples : 6000); // Generate a decent amount
        return dataset;
    }

private:
    // Create simplified templates for digits 0-9 (28x28)
    static std::vector<std::vector<double>> create_digit_templates()
    {
        std::vector<std::vector<double>> templates(10, std::vector<double>(28 * 28, 0.0));

        // Helper to draw a line on a template
        auto draw_line_template = [&](int digit, int r1, int c1, int r2, int c2)
        {
            int dr = std::abs(r2 - r1);
            int dc = std::abs(c2 - c1);
            int sr = (r1 < r2) ? 1 : -1;
            int sc = (c1 < c2) ? 1 : -1;
            int err = dr - dc;
            int r = r1, c = c1;
            while (true)
            {
                if (r >= 0 && r < 28 && c >= 0 && c < 28)
                {
                    templates[digit][r * 28 + c] = 1.0;
                }
                if (r == r2 && c == c2)
                    break;
                int e2 = 2 * err;
                if (e2 > -dc)
                {
                    err -= dc;
                    r += sr;
                }
                if (e2 < dr)
                {
                    err += dr;
                    c += sc;
                }
            }
        };

        // Digit 0: A rectangle/oval shape
        draw_line_template(0, 5, 10, 5, 18);   // Top
        draw_line_template(0, 22, 10, 22, 18); // Bottom
        draw_line_template(0, 5, 10, 22, 10);  // Left
        draw_line_template(0, 5, 18, 22, 18);  // Right

        // Digit 1: Vertical line
        draw_line_template(1, 5, 14, 22, 14);
        draw_line_template(1, 7, 12, 5, 14); // small top bar

        // Digit 2
        draw_line_template(2, 5, 8, 5, 18);   // Top
        draw_line_template(2, 5, 18, 13, 18); // Top-right diag/vert
        draw_line_template(2, 13, 8, 13, 18); // Middle
        draw_line_template(2, 13, 8, 22, 8);  // Middle-left diag/vert
        draw_line_template(2, 22, 8, 22, 18); // Bottom

        // Digit 3
        draw_line_template(3, 5, 8, 5, 18);    // Top
        draw_line_template(3, 13, 10, 13, 18); // Middle
        draw_line_template(3, 22, 8, 22, 18);  // Bottom
        draw_line_template(3, 5, 18, 22, 18);  // Right vertical connector

        // Digit 4
        draw_line_template(4, 5, 15, 22, 15); // Main vertical
        draw_line_template(4, 5, 8, 14, 8);   // Left vertical part
        draw_line_template(4, 14, 8, 14, 18); // Horizontal cross

        // Digit 5
        draw_line_template(5, 5, 8, 5, 18);    // Top
        draw_line_template(5, 5, 8, 13, 8);    // Top-left vertical
        draw_line_template(5, 13, 8, 13, 18);  // Middle
        draw_line_template(5, 13, 18, 22, 18); // Middle-right diag/vert
        draw_line_template(5, 22, 8, 22, 18);  // Bottom

        // Digit 6
        draw_line_template(6, 5, 18, 13, 8); // Top-left curve (approx with line)
        draw_line_template(6, 5, 10, 5, 18);
        draw_line_template(6, 5, 10, 22, 10);  // Left vertical
        draw_line_template(6, 22, 10, 22, 18); // Bottom
        draw_line_template(6, 13, 10, 13, 18); // Middle horizontal bar inside
        draw_line_template(6, 13, 18, 22, 18); // Connect middle bar to bottom right

        // Digit 7
        draw_line_template(7, 5, 8, 5, 18);   // Top bar
        draw_line_template(7, 5, 18, 22, 10); // Diagonal down

        // Digit 8: Two connected ovals/rects
        draw_line_template(8, 5, 10, 5, 18);   // Top of upper
        draw_line_template(8, 13, 10, 13, 18); // Bottom of upper / top of lower
        draw_line_template(8, 22, 10, 22, 18); // Bottom of lower
        draw_line_template(8, 5, 10, 13, 10);  // Left of upper
        draw_line_template(8, 5, 18, 13, 18);  // Right of upper
        draw_line_template(8, 13, 10, 22, 10); // Left of lower
        draw_line_template(8, 13, 18, 22, 18); // Right of lower

        // Digit 9 (like a '6' flipped)
        draw_line_template(9, 13, 18, 22, 8); // Bottom-right curve (approx with line)
        draw_line_template(9, 22, 10, 22, 18);
        draw_line_template(9, 5, 18, 22, 18);  // Right vertical
        draw_line_template(9, 5, 10, 5, 18);   // Top
        draw_line_template(9, 13, 10, 13, 18); // Middle horizontal bar inside
        draw_line_template(9, 5, 10, 13, 10);  // Connect top bar to middle left

        return templates;
    }
};

// Simple drawing interface for console testing
class DrawingInterface
{
private:
    std::vector<double> canvas;
    int width, height;

public:
    DrawingInterface(int w = 28, int h = 28) : width(w), height(h)
    {
        canvas.resize(width * height, 0.0);
    }

    void clear()
    {
        std::fill(canvas.begin(), canvas.end(), 0.0);
    }

    void draw_point(int x, int y, double value = 1.0, int brush_size = 0)
    {
        for (int dy = -brush_size; dy <= brush_size; ++dy)
        {
            for (int dx = -brush_size; dx <= brush_size; ++dx)
            {
                int cur_x = x + dx;
                int cur_y = y + dy;
                if (cur_x >= 0 && cur_x < width && cur_y >= 0 && cur_y < height)
                {
                    // Optional: make brush falloff, for now, solid square
                    canvas[cur_y * width + cur_x] = value;
                }
            }
        }
    }

    // Bresenham's line algorithm (not used in final menu, but useful for templates)
    void draw_line(int x1, int y1, int x2, int y2, double value = 1.0)
    {
        int dx_abs = abs(x2 - x1);
        int dy_abs = abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx_abs - dy_abs;

        while (true)
        {
            draw_point(x1, y1, value); // Draw with current brush size setting if draw_point uses it
            if (x1 == x2 && y1 == y2)
                break;
            int e2 = 2 * err;
            if (e2 > -dy_abs)
            {
                err -= dy_abs;
                x1 += sx;
            }
            if (e2 < dx_abs)
            {
                err += dx_abs;
                y1 += sy;
            }
        }
    }

    void display()
    {
        std::cout << "\nDrawing (0,0 is top-left):" << std::endl;
        std::cout << "  ";
        for (int x = 0; x < width; ++x)
            std::cout << (x % 10); // X-coordinates guide
        std::cout << std::endl;
        for (int y = 0; y < height; ++y)
        {
            std::cout << (y % 10) << " "; // Y-coordinates guide
            for (int x = 0; x < width; ++x)
            {
                char c = canvas[y * width + x] > 0.5 ? '#' : '.';
                std::cout << c;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::vector<double> get_image()
    {
        return canvas;
    }

    // Draw a simple digit (for testing)
    void draw_test_digit(int digit)
    {
        clear();
        std::vector<std::vector<double>> templates = DataLoader::create_digit_templates();
        if (digit >= 0 && digit < 10)
        {
            canvas = templates[digit];
        }
        else
        {
            std::cout << "Test digit " << digit << " not implemented or out of range." << std::endl;
            // Draw a fallback, e.g. a question mark
            draw_line(10, 5, 18, 5);
            draw_line(18, 5, 18, 10);
            draw_line(18, 10, 14, 14);
            draw_line(14, 14, 14, 17);
            draw_point(14, 20); // ?
        }
    }
};

void clear_cin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    std::cout << "Neural Network for Handwritten Digit Recognition" << std::endl;
    std::cout << "================================================" << std::endl;

    NeuralNetwork nn;
    std::string model_filename = "digit_nn_model.dat";

    int choice = 0;
    bool trained_or_loaded = false;
    DrawingInterface drawing(28, 28);

    std::vector<DigitImage> train_data;
    std::vector<DigitImage> test_data;

    // Automatically try to load a model at startup
    std::ifstream f(model_filename.c_str());
    if (f.good())
    {
        f.close();
        std::cout << "Previous model found. Attempting to load..." << std::endl;
        nn.load_model(model_filename);
        trained_or_loaded = true; // Assume loading makes it "trained" for prediction purposes
    }
    else
    {
        f.close();
        std::cout << "No pre-trained model found. Please train or load a model." << std::endl;
    }

    while (true)
    {
        std::cout << "\nOptions:" << std::endl;
        std::cout << "1. Train network on synthetic data" << std::endl;
        std::cout << "2. Load pre-trained model from file (" << model_filename << ")" << std::endl;
        std::cout << "3. Save current model to file (" << model_filename << ")" << std::endl;
        std::cout << "4. Test with a sample template digit" << std::endl;
        std::cout << "5. Draw a digit and predict" << std::endl;
        std::cout << "6. Evaluate on test set (if data loaded/generated)" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice))
        {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            clear_cin();
            continue;
        }
        clear_cin(); // Consume the rest of the line

        if (choice == 0)
        {
            std::cout << "Exiting program." << std::endl;
            break;
        }

        switch (choice)
        {
        case 1:
        {
            std::cout << "Generating synthetic training data..." << std::endl;
            int train_size = 10000; // Increased for potentially better results
            int test_size = 2000;
            train_data = DataLoader::generate_synthetic_data(train_size);
            test_data = DataLoader::generate_synthetic_data(test_size);

            std::cout << "Training on " << train_data.size() << " samples for " << MAX_EPOCHS << " epochs..." << std::endl;
            auto start_time = std::chrono::high_resolution_clock::now();

            for (int epoch = 0; epoch < MAX_EPOCHS; ++epoch)
            {
                std::cout << "Epoch " << epoch + 1 << "/" << MAX_EPOCHS << "..." << std::endl;

                // Shuffle training data
                static std::random_device rd_shuffle;
                static std::mt19937 g_shuffle(rd_shuffle());
                std::shuffle(train_data.begin(), train_data.end(), g_shuffle);

                // Basic batching (iterate through data in BATCH_SIZE chunks)
                for (size_t i = 0; i < train_data.size(); i += BATCH_SIZE)
                {
                    std::vector<DigitImage> batch;
                    for (size_t j = 0; j < BATCH_SIZE && (i + j) < train_data.size(); ++j)
                    {
                        batch.push_back(train_data[i + j]);
                    }
                    if (!batch.empty())
                    {
                        nn.train_batch(batch); // train_batch internally iterates one-by-one
                    }
                }

                if ((epoch + 1) % 5 == 0 || epoch == MAX_EPOCHS - 1)
                { // Evaluate every 5 epochs
                    double train_accuracy = nn.evaluate(train_data);
                    double test_accuracy = nn.evaluate(test_data);
                    std::cout << "Epoch " << epoch + 1 << ": Train Accuracy: " << std::fixed << std::setprecision(4) << train_accuracy
                              << ", Test Accuracy: " << test_accuracy << std::endl;
                }
            }

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
            std::cout << "Training finished in " << duration.count() << " seconds." << std::endl;
            trained_or_loaded = true;
            break;
        }
        case 2:
        {
            nn.load_model(model_filename);
            trained_or_loaded = true; // Assume successful load
            // Optionally, re-evaluate if test data is available
            if (!test_data.empty())
            {
                double accuracy = nn.evaluate(test_data);
                std::cout << "Accuracy on loaded test data: " << std::fixed << std::setprecision(4) << accuracy << std::endl;
            }
            else
            {
                std::cout << "Model loaded. No test data available to evaluate immediately." << std::endl;
            }
            break;
        }
        case 3:
        {
            if (trained_or_loaded)
            {
                nn.save_model(model_filename);
            }
            else
            {
                std::cout << "Model has not been trained or loaded yet. Nothing to save." << std::endl;
            }
            break;
        }
        case 4:
        {
            if (!trained_or_loaded)
            {
                std::cout << "Model not trained or loaded. Please train/load first." << std::endl;
                break;
            }
            int digit_to_test;
            std::cout << "Enter a digit (0-9) to generate a test template: ";
            if (!(std::cin >> digit_to_test) || digit_to_test < 0 || digit_to_test > 9)
            {
                std::cout << "Invalid input. Defaulting to digit 1." << std::endl;
                digit_to_test = 1;
                clear_cin();
            }
            clear_cin();

            drawing.draw_test_digit(digit_to_test);
            drawing.display();

            std::vector<double> image_pixels = drawing.get_image();
            // Preprocessing for test digit:
            // Synthetic templates are already somewhat clean. Normalization is key.
            // Full preprocessing might alter them too much if not careful.
            // For consistency with training, if synthetic training data was fully preprocessed, do it here.
            // If training data was only normalized, only normalize here.
            // Let's assume only normalization was consistently applied for synthetic data for simplicity.
            std::vector<double> processed_image = ImagePreprocessing::normalize(image_pixels);
            // If full preprocessing was used in training synthetic data:
            // std::vector<double> processed_image = ImagePreprocessing::preprocess(image_pixels, 28, 28);

            if (processed_image.empty() || processed_image.size() != INPUT_SIZE)
            {
                std::cout << "Error processing test image." << std::endl;
                break;
            }

            int prediction = nn.predict(processed_image);
            std::cout << "Model prediction for template '" << digit_to_test << "': " << prediction << std::endl;
            break;
        }
        case 5:
        {
            if (!trained_or_loaded)
            {
                std::cout << "Model not trained or loaded. Please train/load first." << std::endl;
                break;
            }
            drawing.clear();
            std::cout << "Simple Drawing Interface:" << std::endl;
            std::cout << "Enter x y coordinates (0-27 for each) to mark a pixel." << std::endl;
            std::cout << "Use a brush size of 0 for single pixel, 1 for 3x3 brush." << std::endl;
            std::cout << "Type '-1 -1' to finish drawing." << std::endl;

            int x, y, brush;
            while (true)
            {
                drawing.display();
                std::cout << "Enter x y brush_size (e.g., 14 14 1): ";
                if (!(std::cin >> x >> y >> brush))
                {
                    std::cout << "Invalid input. Try again." << std::endl;
                    clear_cin();
                    continue;
                }
                clear_cin();

                if (x == -1 && y == -1)
                {
                    break;
                }
                if (x < 0 || x >= 28 || y < 0 || y >= 28)
                {
                    std::cout << "Coordinates out of bounds (0-27). Try again." << std::endl;
                }
                else if (brush < 0 || brush > 3)
                { // Limit brush size
                    std::cout << "Brush size out of bounds (0-3). Try again." << std::endl;
                }
                else
                {
                    drawing.draw_point(x, y, 1.0, brush);
                }
            }

            std::cout << "Final drawing:" << std::endl;
            drawing.display();

            std::vector<double> user_image_raw = drawing.get_image();
            std::vector<double> processed_user_image = ImagePreprocessing::preprocess(user_image_raw, 28, 28);

            if (processed_user_image.empty() || processed_user_image.size() != INPUT_SIZE)
            {
                std::cout << "Error processing drawn image." << std::endl;
                break;
            }

            int prediction = nn.predict(processed_user_image);
            std::cout << "Model prediction for your drawing: " << prediction << std::endl;
            break;
        }
        case 6:
        {
            if (!trained_or_loaded)
            {
                std::cout << "Model not trained or loaded." << std::endl;
                break;
            }
            if (test_data.empty())
            {
                std::cout << "No test data available. Please train first (Option 1) to generate test data." << std::endl;
            }
            else
            {
                double accuracy = nn.evaluate(test_data);
                std::cout << "Accuracy on current test set: " << std::fixed << std::setprecision(4) << accuracy << std::endl;
            }
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }

    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

//function to perform convolution operation on flatten array ...
void CNN(int channels, 
         int input_height, int input_width,   // Dimensions of input matrix
         const vector<int>& input, 
         int kernel_height, int kernel_width, // Dimensions of kernel matrix
         const vector<int>& kernel, 
         int no_ofKernels, 
         vector<int>& output, 
         int stride = 1, 
         bool padding = false) {
        
    // Calculating the  output dimensions height , width 
    int padded_input_height = input_height + (padding ? 2 : 0);  // Add padding if necessary
    int padded_input_width = input_width + (padding ? 2 : 0);
    
    //using ((n-f) / stride )+1 for individual heights and width ...
    int output_height = ((padded_input_height - kernel_height) / stride) + 1;  // Output height
    int output_width = ((padded_input_width - kernel_width) / stride) + 1;     // Output width

    // if padding is true initiallizing all values to zero
    // and copying the existing values in the center to achieve padding opeartion
    // 
    vector<int> padded_input;
    if (padding) {
        padded_input.resize(padded_input_height * padded_input_width * channels, 0);
        for (int c = 0; c < channels; ++c) {
            for (int i = 0; i < input_height; ++i) {
                for (int j = 0; j < input_width; ++j) {
                    padded_input[(c * padded_input_height * padded_input_width) + (i + 1) * padded_input_width + (j + 1)] = 
                        input[(c * input_height * input_width) + i * input_width + j];
                }
            }
        }
    } else {
        padded_input = input;  // No padding applied
    }

    //to visualize the padded array 
    if(padding){
        for (int c = 0; c < channels; ++c) {
        std::cout << "Channel " << c + 1 << ":\n";
            for (int i = 0; i < padded_input_height; ++i) {
                for (int j = 0; j < padded_input_width; ++j) {
                    std::cout << padded_input[(c * padded_input_height * padded_input_width) + i * padded_input_width + j] << " ";
                }
            std::cout << endl;
    }
    std::cout << endl;
    }
    }



    //implementing convolution 
    // For each kernel
    for (int n = 0; n < no_ofKernels; ++n) {  
        //height wise ... 
        for (int h = 0; h < output_height; ++h) {
            //width wise ...
            for (int w = 0; w < output_width; ++w) {
                int sum = 0;
                //NHWC ... 
                for (int c = 0; c < channels; ++c) {  // For each channel
                    //performimg kernel on it ...
                    for (int kh = 0; kh < kernel_height; ++kh) {
                        for (int kw = 0; kw < kernel_width; ++kw) {
                            // Compute the convolution sum
                            //input[(c * NH * NW) + (i * NW) + j] 
                            //here NH is input_height(with padding )
                            //NW is input_width(with padding )+
                            //(channels * height * width ) + ( row * stride + kernel_row) * width + (column * stride + kernel_column )

                            int input_index = (c * padded_input_height * padded_input_width) + 
                                              (h * stride + kh) * padded_input_width + 
                                              (w * stride + kw);
                            
                            int kernel_index = (c * kernel_height * kernel_width) + 
                                               (kh * kernel_width) + kw;
                            
                            sum += padded_input[input_index] * kernel[kernel_index];
                        }
                    }
                }
                output.push_back(sum);  // Storing the result
            }
        }
    }
}


int main() {
    int channels = 3;
    int input_height = 4;
    int input_width = 5;  // Input matrix dimensions (4x5x3)
    vector<int> input = {
        // A simple 4x5x3 input for illustration (3 channels of 4x5 each)
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,    // Channel 1
        20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 ,   // Channel 2
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20     // Channel 3
    };

    int kernel_height = 3;
    int kernel_width = 3;  // Kernel matrix dimensions (3x3x3)
    vector<int> kernel = {
        // A simple 3x3x3 kernel
        1, 0, 1, 0, 1, 0, 1, 0, 1,   // Channel 1
        1, 0, 1, 0, 1, 0, 1, 0, 1,   // Channel 2
        1, 0, 1, 0, 1, 0, 1, 0, 1    // Channel 3
    };

    int no_ofKernels = 1;  // Number of kernels to apply
    vector<int> output;    // To store the result of convolution

    CNN(channels, input_height, input_width, input, kernel_height, kernel_width, kernel, no_ofKernels, output, 1, true);  // No padding, stride 1

    // Output the results
    cout << "Output after convolution: " << endl;
    for (int i = 1; i < output.size(); ++i) {
        cout << output[i-1] << " ";
        if ((i) % ((5)) == 0) cout << endl;  // Formatting output based on output width
    }

    return 0;
}

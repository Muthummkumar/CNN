#include <iostream>
#include <vector>

typedef  std::vector<std::vector<std::vector<int>>> Matrix_3D;
//typedef std::vector<std::vector<int>> Matrix_2D;

std::vector<std::vector<int>> conv_3D(const Matrix_3D& input, const Matrix_3D& kernel, int strides = 1, bool padding = false){
    int no_channels = input.size();
    
}




std::vector<std::vector<int>> conv_2D(const std::vector<std::vector<int>>& input, const std::vector<std::vector<int>>& kernel, int strides = 1, bool padding = false) {

    //extracting size & height , width of matrix and kernal 
    int input_height = input.size();
    int input_width = input[0].size();
    int kernelSize = kernel.size();
    
    //The formula for padding to maintain the same output size is:
    //(kernal_size - 1) / 2
    int pad = 0;
    if(padding) {pad = (kernel.size() - 1) / 2;}


    //to initialize the size of output matrix 
    //( (input matrix size(h || w) - kernal (h || w) - amount of padding ) / strides  ) + 1
    int output_height = ((input_height - kernelSize + 2 * pad) / strides ) + 1;
    int output_width =  ((input_width - kernelSize + 2 * pad) /strides ) + 1;
    

    //output matrix (size , data needs to fill ) in this case (rows , array())
    std::vector<std::vector<int>> output(output_height, std::vector<int>(output_width, 0));


    //convolution operation
    //two loops to perform sliding operation from left to right row wise 
    //top to bottom column wise
    //hop based on stride value
    for(int col_I = 0;col_I <= input_height-kernelSize; col_I += strides ){

        for(int row_I = 0;row_I <= input_width-kernelSize; row_I += strides){

            //Apply the kernal on the slided piece of matrix 
            int sum = 0;
            for(int K_I = 0;K_I < kernelSize;K_I++){
                for (int K_J = 0; K_J < kernelSize; K_J++)
                {
                    sum += input[col_I+K_I][row_I+K_J] * kernel[K_I][K_J];
                }
                
            }

            output[col_I /strides][row_I / strides] = sum;
        }
    }

    return output;
}

// Helper function to print a matrix
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Initialize a 9x9 input image
    std::vector<std::vector<int>> input_image(9, std::vector<int>(9));
    int num = 1;

    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            input_image[i][j] = num++;
        }
    }

    // Print the input image
    std::cout << "Input image:" << std::endl;
    printMatrix(input_image);

    // Define a 3x3 kernel
    std::vector<std::vector<int>> kernel = {
        {1, 0, -1},
        {1, 0, -1},
        {1, 0, -1}
    };

    // Perform the convolution
    std::vector<std::vector<int>> output = conv_2D(input_image, kernel,2,true);

    // Print the output matrix
    std::cout << "\nOutput after convolution:" << std::endl;
    printMatrix(output);

    return 0;
}

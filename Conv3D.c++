#include <iostream>
#include <vector>


typedef  std::vector<std::vector<std::vector<int>>> Matrix_3D;
typedef std::vector<std::vector<int>> Matrix_2D;


//function to perform padding on the input matrix 
// function to pad the input matrix
//padding operation is costly because it has to copy the entire array into new one 
/*
Matrix_3D padInput(const Matrix_3D& input, int pad) {
    int input_channels = input.size();
    int input_height = input[0].size();
    int input_width = input[0][0].size();

    // Create a padded matrix
    Matrix_3D padded(input_channels, Matrix_2D(input_height + 2 * pad, std::vector<int>(input_width + 2 * pad, 0)));

    // Copy the input matrix into the center of the padded matrix
    for (int ch = 0; ch < input_channels; ch++) {
        for (int i = 0; i < input_height; i++) {
            for (int j = 0; j < input_width; j++) {
                padded[ch][i + pad][j + pad] = input[ch][i][j];
            }
        }
    }

    return padded;
}*/

Matrix_3D padInput(const Matrix_3D& input , int padding ){
    int ch = input.size();
    int height = input[0].size();
    int width = input[0][0].size();

    for (size_t CH_I = 0; CH_I < ch; CH_I++)
    {
        for(size_t COL_I = 0;COL_I < height;COL_I++){
            
            for(size_t ROW_I = 0 ;ROW_I < width;ROW_I++){




            }
        }
    }
    
}

std::vector<Matrix_2D> conv_3D(const Matrix_3D& input, const std::vector<Matrix_3D>& kernels, int strides = 1, bool padding = false){
    
    //inputMatrix parameters ch, h, w
    int input_channels = input.size();
    int input_height = input[0].size();
    int input_width = input[0][0].size();

    //kernal parameters 
    //no of filters , no of chanels  , kernelsize
    int kernelSize = kernels[0][0].size();
    int no_kernels = kernels.size();

    //here for RGB image using 3 channels so we are using the same values 
    //int no_KerCh = kernels[0].size(); 

    int pad = 0;
    if(padding) {
        pad = (kernelSize - 1) / 2;
    }



    int output_height = (input_height - kernelSize + 2 * pad) / strides + 1;
    int output_width = (input_width - kernelSize + 2 * pad) / strides + 1;


    // int output_height = input_height-kernelSize + 1;
    // int output_width = input_width-kernelSize + 1;

    
    std::vector<Matrix_2D> result_images;

    for (int i = 0; i < no_kernels; i++)
    {
        Matrix_2D output(std::vector<std::vector<int>>(output_height, std::vector<int>(output_width, 0)));
        //using all the kernels in the container ...
        
    
    {
        //iterate over the coloumns 
        for(int col_I = 0;col_I <= input_height-kernelSize; col_I += strides ){
            
            //iterate overs row
            for(int row_I = 0;row_I <= input_width-kernelSize; row_I += strides){

            //Apply the kernal on the slided piece of matrix 
            int sum = 0;

            //input image and kernals having same no of channels so using the same iterator
            for (int CH_I = 0; CH_I < input_channels; CH_I++){

            
            for(int K_I = 0;K_I < kernels[i][CH_I].size();K_I++){

                for (int K_J = 0; K_J < kernels[i][CH_I].size(); K_J++)
                {
                        sum += input[CH_I][col_I+K_I][row_I+K_J] * kernels[i][CH_I][K_I][K_J];
                }  
            }

            }

                output[col_I /strides][row_I / strides] += sum;

            }
        }
        result_images.push_back(output);
    }
       
        }
    //returning the container having all the computed 2D Mat 
    return result_images;
}

void printMatrix(const Matrix_2D& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Example input matrix (3D input with 3 channels, 3x3 in each channel)
    Matrix_3D input = {
        { // Channel 1
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8, 9}
        },
        { // Channel 2
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8, 9}
        },
        { // Channel 3
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8, 9}
        }
    };

    // 3x3x3 kernel (one 3x3 kernel for each of the 3 channels)
    std::vector<Matrix_3D> kernels = {
        { // Kernel 1 (3 channels, each 3x3)
            { {1, 0, -1}, {1, 0, -1}, {1, 0, -1} }, // Channel 1
            { {1, 0, -1}, {1, 0, -1}, {1, 0, -1} }, // Channel 2
            { {1, 0, -1}, {1, 0, -1}, {1, 0, -1} }  // Channel 3
        }
    };

    // Perform 3D convolution (no padding, stride = 1)
    std::vector<Matrix_2D> output = conv_3D(input, kernels, 1, false);

    // Print the result of the convolution
    std::cout << "Output from Convolution (Kernel 1):" << std::endl;
    printMatrix(output[0]);

    return 0;
}

#include "MlpNetwork.h"

MlpNetwork::MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]) :
    _layers{Dense(weights[0], biases[0], activation::relu),
            Dense(weights[1], biases[1], activation::relu),
            Dense(weights[2], biases[2], activation::relu),
            Dense(weights[3], biases[3], activation::softmax)}
{}

digit MlpNetwork::operator()(Matrix m) const
{
    m.vectorize();
    for(const auto &layer: _layers)
    {
        m = layer(m);
    }

    int res = m.argmax();

    return {res, m[res]};
}

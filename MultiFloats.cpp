#include <iostream>
#include <bitset>
using namespace std;

bitset<32> sumaope(const bitset<32>& bits1, const bitset<32>& bits2) {
    bitset<32> resultado;
    bool carry = false;
    for (int i = 31; i >= 0; --i) {
        bool bit1 = bits1[i];
        bool bit2 = bits2[i];
        bool suma = bit1 ^ bit2 ^ carry;
        carry = (bit1 & bit2) | (carry & (bit1 ^ bit2));
        resultado[i] = suma;
    }
    return resultado;
}

bitset<32> multiplicaope(const bitset<32>& bits1, const bitset<32>& bits2) {
    bitset<32> resultado(0);
    for (int i = 0; i < 32; ++i) {
        if (bits2[i]) {
            resultado ^= (bits1 << i);
        }
    }
    return resultado;
}

float conversion(const bitset<32>& bits) {
    uint32_t valorEntero = bits.to_ulong();
    return *reinterpret_cast<float*>(&valorEntero);
}

int main() {
    float fx;
    float fy;
    do{
        cout << "Ingresa el valor del primer float (x): ";
        cin >> fx;
    } while(fx >= 0);

    do{
        cout << "Ingresa el valor del segundo float (y): ";
        cin >> fy;
    } while(fy >= 0);

    uint32_t castx = *reinterpret_cast<uint32_t*>(&fx);
    uint32_t casty = *reinterpret_cast<uint32_t*>(&fy);

    bitset<32> fpx(castx);
    bitset<32> fpy(casty);

    cout << "Signo de x: " << fpx[31] << ", Exponente de x: " << ((castx >> 23) & 0xFF) << ", Mantisa de x: " << (castx & 0x7FFFFF) << endl;
    cout << "Signo de y: " << fpy[31] << ", Exponente de y: " << ((casty >> 23) & 0xFF) << ", Mantisa de y: " << (casty & 0x7FFFFF) << endl;

    bitset<32> resultadoSuma = sumaope(fpx, fpy);
    cout << "Suma de las representaciones binarias: " << resultadoSuma << endl;
    float c_resultadoSuma = conversion(resultadoSuma);
    cout << "Conversion de binario a float: " << c_resultadoSuma << endl;

    bitset<32> rptamult = multiplicaope(fpx, fpy);
    cout << "Multiplicación de las representaciones binarias: " << rptamult << endl;

    return 0;
}
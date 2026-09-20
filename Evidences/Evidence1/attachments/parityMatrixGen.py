def generate_hsiao_matrix(data_bits=32, parity_bits=7, weight=3):
    """Generates integers with a specific Hamming weight for SEC-DED matrices."""
    matrix = []
    max_val = 1 << parity_bits
    
    for candidate in range(max_val):
        if bin(candidate).count('1') == weight:
            matrix.append(candidate)
            if len(matrix) == data_bits:
                break
                
    return matrix


def export_c_array(matrix):
    print(f"static const uint8_t P_MATRIX[{len(matrix)}] = {{")
    for i in range(0, len(matrix), 8):
        chunk = matrix[i:i + 8]
        hex_formatted = ", ".join(f"0x{val:02X}" for val in chunk)
        trailing_comma = "," if i + 8 < len(matrix) else ""
        print(f"    {hex_formatted}{trailing_comma}")
    print("};")


if __name__ == "__main__":
    # IPV4 (since \binom_{7}{3} = 35 > 32)
    p_matrix = generate_hsiao_matrix(data_bits=32, parity_bits=7, weight=3)
    export_c_array(p_matrix)

    # DATE (since \binom_{8}{3} = 56)
    p_matrix_56 = generate_hsiao_matrix(data_bits=56, parity_bits=8, weight=3)
    export_c_array(p_matrix_56)
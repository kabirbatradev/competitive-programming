import re

def minify_cpp(file_path):
    with open(file_path, 'r') as f:
        code = f.read()
    
    # Remove comments
    code = re.sub(r'//.*', '', code)  # Single-line comments
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)  # Multi-line comments
    
    # Remove unnecessary whitespace
    code = re.sub(r'\s+', ' ', code)  # Replace multiple spaces with one
    code = re.sub(r'\s*([{}();,+\-*/%<>=&|^!~])\s*', r'\1', code)  # Remove spaces around operators and delimiters
    code = re.sub(r';\s*', ';', code)  # Remove spaces after semicolons
    
    # Remove newlines
    code = code.replace('\n', '')
    
    return code

# Input and output file paths
input_file = 'VinDiagramsMinified.cpp'
output_file = 'minified_code.cpp'

# Minify the file
minified_code = minify_cpp(input_file)
with open(output_file, 'w') as f:
    f.write(minified_code)

print(f"Minified code written to {output_file}")

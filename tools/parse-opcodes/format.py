import json

# data = json.load("Opcodes.json")

with open('Opcodes.json') as user_file:
    data = user_file.read()

# Load JSON data
opcodes = json.loads(data)["cbprefixed"]

# Process and print each opcode entry
for opcode_hex, opcode_data in opcodes.items():
    mnemonic = opcode_data["mnemonic"]
    cycles = opcode_data["cycles"]

    temp = ""

    if len(cycles) > 1:
        for i in range(len(cycles)):
            temp += str(cycles[i]) 
            if i != len(cycles) - 1:
                temp += ", "
            
    else:
        temp = str(cycles[0]) 
    temp = "{" + temp + "}"
    cycles = temp 
    bytes_count = opcode_data["bytes"]

    
    print(f'Opcode({opcode_hex}, "{mnemonic}", {cycles}, {bytes_count}),')

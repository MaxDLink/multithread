import openai
import json # for getting errors json file from lab one 
import sys # for getting prompt from customjob.cpp
import os #for checking if directory exists and creating it if it doesn't in else statement 
import re #for fixing invalid escape characters in json string with correct_invalid_escapes() function

def correct_invalid_escapes(json_string):
    # Replace invalid escape sequences like '\_' with '_'
    corrected_string = re.sub(r'\\_', '_', json_string)
    return corrected_string

def parseLLMFixes(fixed_code_json_string):
    try:
        # The delimiter to start the JSON data for fixed code
        delimiter = "Here are the fixed .cpp files:"
        json_data = fixed_code_json_string
        
        if delimiter in json_data:
            # Find the start of the actual JSON content
            json_start = json_data.find(delimiter) + len(delimiter)
            json_content = json_data[json_start:]
            
            # Find the start and end of the JSON data block enclosed in triple backticks
            json_data_start = json_content.find("```json") + len("```json")
            json_data_end = json_content.find("```", json_data_start)
            json_data = json_content[json_data_start:json_data_end].strip()
        else:
            raise ValueError("Delimiter not found in the response text.")

        # Parse the JSON data
        response_data = json.loads(json_data)

        # Dictionary to hold the formatted code blocks
        formatted_code_blocks = {}

        # Iterate through each item in the response data
        for item in response_data:
            # Extract the file path and the fixed code
            file_path = item["File Path"]
            fixed_code = item["Fixed .cpp"]

            # Add the fixed code to the dictionary
            formatted_code_blocks[file_path] = fixed_code

        print("Formatted code blocks parsed successfully!")
        return formatted_code_blocks

    except ValueError as e:
        # Handle errors such as the delimiter not being found
        print("Failed to process the LLM response:", e)
        return None
    except json.JSONDecodeError as e:
        # Handle JSON parsing errors
        print("Failed to parse JSON data:", e)
        return None

def writeToFiles(formatted_code_blocks):
    print("\nWriting fixed code to appropriate files!\n")
    # Check if formatted_code_blocks is not None
    if formatted_code_blocks:
        # Iterate through the dictionary and write its contents to files
        for file_path, code_block in formatted_code_blocks.items():
            # Ensure the directory exists
            directory = os.path.dirname(file_path)
            if not os.path.exists(directory):
                os.makedirs(directory)

            # Write the fixed code to the corresponding file
            try:
                with open(file_path, 'w') as file:
                    file.write(code_block)
                    print(f"Successfully wrote to {file_path}")
            except IOError as e:
                print(f"Failed to write to {file_path}: {e}")

    else:
        print("No formatted code blocks were parsed.")
        
def runModel(modelName, prompt):
    # Specify the model you want to use and make the API request
    model = modelName
    try:
        response = openai.Completion.create(
            model=model,
            prompt=prompt,
            max_tokens=5000,
            temperature=0.28,
            top_p=0.95,
            n=1,
            echo=True,
            stream=False
        )
        return response
    except Exception as e:
        print("An error occurred:", e)
        return None
    
    
    

print("LLM RUNNING!!!!\n") 
# Set the base URL to your local server
openai.api_base = "http://localhost:4891/v1" #TODO - pass local host 4891 to LLMCall.py from customjob.cpp after passed to customJob from main? URL NOT IP SO NO? 

# Since it's a local server, API key is not required
openai.api_key = "not needed for a local LLM"



# print("\n CODE: " + code + "\n"); #TODO - remove this line. For testing purposes only
# Set up the prompt and other parameters for the API request
#prompt = "Answer question based on the context. Context: Here is code in a json file format with errors. Please fix these errors and add a description of what you did to fix the errors. Question: " + code; 
# Get the prompt from command line arguments
prompt = sys.argv[1] if len(sys.argv) > 1 else "Default prompt if not provided"
# TODO - make sure switching model names pings different models in GPT4ALL without manually changing models in GPT4ALL... 
#modelName = "Mistral OpenOrca" # Mistral OpenOrca # Mistral Instruct. 
#modelName = "mistral-7b-openorca.Q4_0.gguf"
modelName = "mistral-7b-instruct-v0.1.Q4_0.gguf"
# TODO - remember to change default model used in GPT4ALL???? OR IS THIS NOT NEEDED?
print("\nthis is the prompt being put into ", modelName, ": ", prompt, "\n")

# Call the runModel function to run the specified AI model 
# can either use "Minstrel OpenOrca" or "GPT4All Falcon"
response = runModel(modelName, prompt)

#if(modelName == "Mistral OpenOrca"): 
if(modelName == "mistral-7b-openorca.Q4_0.gguf"):
    output_file_path = "./Data/OpenOrca-Response.json"
    print("\n\nMistral OpenOrca model output path!\n\n")
elif(modelName == "mistral-7b-instruct-v0.1.Q4_0.gguf"):
    output_file_path = "./Data/MistralInstruct-Response.json"
    print("\n\nMistral Instruct model output path!\n\n")
else: 
    print("\n\nERROR: Model name not recognized!\n\n")
# Now, write the response to a JSON file
with open(output_file_path, "w") as output_file:
    json.dump(response, output_file, indent=4)
    
# turn response into string to print to console
responseString = json.dumps(response, indent=4) 
    
print("---THE AI RESPONSE-----\n\n\n\n\n " +  responseString + "\n\n\n\n\n--------END OF AI RESPONSE---------")

#TODO - should only be done if the specific prompt is for the flowscript interpretation task
#if(prompt == "﻿Please write flowscript code based on the context. Context: Here is flowscript for you to base your flowscript off of. The flowScript must connect jobs in order where 'compilejob' is the first job, 'parsingjob' is the second job, and 'outputjob' is the third job. Only those three jobs should be created. Question: Please write flowscript that mimics this flowscript: digraph JobGraph {compilejob -> parsingjob;parsingjob -> outputjob;}"): 

#extract the text from the response
generated_text = response['choices'][0]['text']
# Split the text into lines
lines = generated_text.splitlines()

# Find the line that starts with "digraph JobGraph {"
start_index = next((i for i, line in enumerate(lines) if line.strip().startswith("digraph JobGraph {")), None)

if start_index is not None:
    # Find the matching closing brace "}"
    end_index = next((i for i, line in enumerate(lines[start_index:], start=start_index) if line.strip() == "}"), None)

    if end_index is not None:
        # Extract the "digraph JobGraph { ... }" part
        extracted_text = "\n".join(lines[start_index:end_index + 1])

        # Specify the output file path
        output_file_path = "./Data/LLM-Flowscript-Response.txt"

        # Write the extracted text to a .txt file
        with open(output_file_path, "w") as output_file:
            output_file.write(extracted_text)
else:
    print("Fixing code!") 
    # turn response into string to print to console
    responseString = json.dumps(response, indent=4)

    #print("\n\n\n\nresponse WITH CODE FIXES: ", responseString, "\n\n\n\n")
    
    
    # Extract the LLM's response
    response_text = response['choices'][0]['text']

    # Remove the prompt from the response to get only the LLM's response
    fixed_code_json_string = response_text.replace(prompt, '').strip()

    print("\n\n\n RESPONSE WITH JUST FIXES: ", fixed_code_json_string, "\n\n\n")
    #check for invalid escape characters 
    fixed_code_json_string = correct_invalid_escapes(fixed_code_json_string)
    
    # Parse the LLM's response to get the fixed code blocks
    formatted_code_blocks = parseLLMFixes(fixed_code_json_string) #fixed_code_json_string is the response text from LLM with just the fixes. This should be parsed to get ready to write to files. 
    
       
    writeToFiles(formatted_code_blocks) #TODO - write to files.

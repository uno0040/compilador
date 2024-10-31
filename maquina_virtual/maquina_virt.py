import tkinter as tk
from tkinter import filedialog, messagebox
import os

def run_compiler():
    # Placeholder function for the "Run" functionality
    messagebox.showinfo("Run", "Compiling...")

def debug_code():
    # Placeholder function for the "Debug" functionality
    messagebox.showinfo("Debug", "Debugging...")

def import_file():
    file_path = filedialog.askopenfilename(filetypes=[("OBJ files", "*.obj")])
    if file_path:
        with open(file_path, "r") as file:
            content = file.read()
            entrada_text.insert("1.0", content)

# Initialize the main window
root = tk.Tk()
root.title("Maquina Virtual")
root.geometry("900x650")
root.configure(bg="#2c3e50")  # Background color of the main window

# Navbar
navbar = tk.Frame(root, bg="#34495e", bd=1, relief="raised")
navbar.pack(side="top", fill="x")

# Title in Navbar
title_label = tk.Label(navbar, text="Maquina Virtual", font=("Helvetica", 16, "bold"), fg="white", bg="#34495e")
title_label.pack(side="left", padx=10)

# Run Button
run_button = tk.Button(navbar, text="Run", command=run_compiler, font=("Helvetica", 12, "bold"), bg="#27ae60", fg="white", activebackground="#2ecc71", width=8)
run_button.pack(side="right", padx=10, pady=10)

# Debug Button
debug_button = tk.Button(navbar, text="Debug", command=debug_code, font=("Helvetica", 12, "bold"), bg="#e67e22", fg="white", activebackground="#f39c12", width=8)
debug_button.pack(side="right", padx=10)

# Import Button
import_button = tk.Button(navbar, text="Import", command=import_file, font=("Helvetica", 12, "bold"), bg="#3498db", fg="white", activebackground="#2980b9", width=8)
import_button.pack(side="right", padx=10)

# Main Container
container = tk.Frame(root, bg="#2c3e50")
container.pack(fill="both", expand=True, padx=10, pady=10)

# Entrada and Saida Text Boxes
left_frame = tk.Frame(container, bg="#2c3e50")
left_frame.pack(side="left", fill="both", expand=True, padx=5, pady=5)

entrada_label = tk.Label(left_frame, text="Entrada", font=("Helvetica", 12, "bold"), bg="#2c3e50", fg="white")
entrada_label.pack()
entrada_text = tk.Text(left_frame, height=13, font=("Helvetica", 10), bg="#ecf0f1", fg="#2c3e50")
entrada_text.pack(fill="both", padx=5, pady=5)

saida_label = tk.Label(left_frame, text="Saida", font=("Helvetica", 12, "bold"), bg="#2c3e50", fg="white")
saida_label.pack()
saida_text = tk.Text(left_frame, height=16, font=("Helvetica", 10), bg="#ecf0f1", fg="#2c3e50")
saida_text.pack(fill="both", padx=5, pady=5)

# Table for Memory
memory_frame = tk.Frame(container, bg="#2c3e50")
memory_frame.pack(side="left", padx=10, pady=10)

memory_label = tk.Label(memory_frame, text="Memoria", font=("Helvetica", 12, "bold"), bg="#2c3e50", fg="white")
memory_label.pack()
memory_table = tk.Text(memory_frame, width=20, height=30, font=("Helvetica", 10), bg="#ecf0f1", fg="#2c3e50")
memory_table.pack(padx=5, pady=5)

# Table for .obj Instructions
instructions_frame = tk.Frame(container, bg="#2c3e50")
instructions_frame.pack(side="left", padx=10, pady=10)

instructions_label = tk.Label(instructions_frame, text="Instruções", font=("Helvetica", 12, "bold"), bg="#2c3e50", fg="white")
instructions_label.pack()
instructions_table = tk.Text(instructions_frame, width=40, height=30, font=("Helvetica", 10), bg="#ecf0f1", fg="#2c3e50")
instructions_table.pack(padx=5, pady=5)

root.mainloop()

import tkinter as tk
from tkinter import filedialog, messagebox
import subprocess

class EditorTexto:
    def __init__(self, root):
        self.root = root
        self.root.title("Editor de Texto")
        self.text_area = tk.Text(self.root, wrap='word', undo=True)
        self.text_area.pack(fill=tk.BOTH, expand=1)

        self.menubar = tk.Menu(self.root)
        self.root.config(menu=self.menubar)

        self.file_menu = tk.Menu(self.menubar, tearoff=0)
        self.file_menu.add_command(label="Abrir", command=self.abrir_arquivo)
        self.file_menu.add_command(label="Salvar", command=self.salvar_arquivo)
        self.file_menu.add_separator()
        self.file_menu.add_command(label="Sair", command=self.root.quit)
        self.menubar.add_cascade(label="Arquivo", menu=self.file_menu)

        self.compile_menu = tk.Menu(self.menubar, tearoff=0)
        self.compile_menu.add_command(label="Compilar", command=self.compilar_codigo)
        self.menubar.add_cascade(label="Executar", menu=self.compile_menu)

        self.output_area = tk.Text(self.root, height=10, bg="#f0f0f0", state='disabled')
        self.output_area.pack(fill=tk.BOTH)

        self.file_path = None

    def abrir_arquivo(self):
        self.file_path = filedialog.askopenfilename(filetypes=[("Text Files", "*.txt"), ("All Files", "*.*")])
        if self.file_path:
            with open(self.file_path, "r", encoding="utf-8") as file:
                self.text_area.delete(1.0, tk.END)
                self.text_area.insert(1.0, file.read())

    def salvar_arquivo(self):
        if not self.file_path:
            self.file_path = filedialog.asksaveasfilename(defaultextension=".txt", filetypes=[("Text Files", "*.txt")])
        if self.file_path:
            with open(self.file_path, "w", encoding="utf-8") as file:
                file.write(self.text_area.get(1.0, tk.END))
                messagebox.showinfo("Salvar Arquivo", "Arquivo salvo com sucesso!")

    def compilar_codigo(self):
        if not self.file_path:
            messagebox.showwarning("Compilar", "Por favor, salve o arquivo antes de compilar.")
            return
        try:
            self.salvar_arquivo()  # Salvar alterações antes de compilar
            result = subprocess.run(["compilador.exe", self.file_path], text=True, capture_output=True)
            output = f"Saída:\n{result.stdout}\n\nErros:\n{result.stderr}"
        except FileNotFoundError:
            output = "Erro: O arquivo 'compilador.exe' não foi encontrado."
        except Exception as e:
            output = f"Erro ao executar o compilador: {e}"
        self.mostrar_saida(output)

    def mostrar_saida(self, output):
        self.output_area.config(state='normal')
        self.output_area.delete(1.0, tk.END)
        self.output_area.insert(1.0, output)
        self.output_area.config(state='disabled')

if __name__ == "__main__":
    root = tk.Tk()
    editor = EditorTexto(root)
    root.mainloop()

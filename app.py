import serial
import threading
import tkinter as tk
from tkinter import ttk
import re

PORT = "/dev/ttyACM0"
BAUD = 38400
HISTORY_MAX = 5

root = tk.Tk()
root.title("Floor Sensor Visualizer")
root.configure(bg="#f4f4f4")

# ----------------- STYLE -----------------
FONT_MAIN = ("Segoe UI", 12, "bold")
FONT_ADC = ("Segoe UI", 11)
FONT_HISTORY = ("Segoe UI", 11)
FONT_POS = ("Segoe UI", 14, "bold")
COLOR_BG = "#f4f4f4"
COLOR_TILE = "#d9d9d9"
COLOR_ACTIVE = "#ff4c4c"
COLOR_FRAME = "#e6e6e6"

style = ttk.Style()
style.theme_use("clam")
style.configure("TProgressbar", troughcolor="#e0e0e0", bordercolor="#e0e0e0", background="#4a90e2")

# ----------------- UKŁAD -----------------
frame_grid = tk.LabelFrame(root, text="Floor Map", bg=COLOR_FRAME, font=FONT_MAIN)
frame_grid.grid(row=0, column=0, padx=20, pady=20)

cells = {}
for r in range(1, 6):
    for c, letter in enumerate(["A", "B", "C"], start=1):
        lbl = tk.Label(
            frame_grid, text=f"{letter}{r}", width=6, height=3,
            bg=COLOR_TILE, relief="raised", font=FONT_MAIN, bd=2
        )
        lbl.grid(row=r, column=c, padx=6, pady=6)
        cells[f"{letter}{r}"] = lbl

frame_adc = tk.LabelFrame(root, text="ADC Monitor", bg=COLOR_FRAME, font=FONT_MAIN)
frame_adc.grid(row=0, column=1, padx=20, pady=20, sticky="n")

adc_labels = []
adc_bars = []
for i in range(4):
    lbl = tk.Label(frame_adc, text=f"ADC{i+1}: --- mV", font=FONT_ADC, bg=COLOR_FRAME)
    lbl.pack(pady=3)
    adc_labels.append(lbl)

    pb = ttk.Progressbar(frame_adc, length=220, maximum=3300, mode="determinate")
    pb.pack(pady=3)
    adc_bars.append(pb)

frame_history = tk.LabelFrame(root, text="Position History", bg=COLOR_FRAME, font=FONT_MAIN)
frame_history.grid(row=1, column=1, padx=20, pady=10, sticky="n")

history_var = [tk.StringVar(value="---") for _ in range(HISTORY_MAX)]
for i in range(HISTORY_MAX):
    lbl = tk.Label(frame_history, textvariable=history_var[i], font=FONT_HISTORY,
                   bg="#ffffff", width=20, relief="groove", anchor="w", padx=8)
    lbl.pack(pady=2)

pos_var = tk.StringVar(value="None")
pos_label = tk.Label(root, textvariable=pos_var, font=FONT_POS, bg=COLOR_BG, fg="#333")
pos_label.grid(row=2, column=0, columnspan=2, pady=15)

# ----------------- LOGIKA -----------------
buffer = []
current_pos = None
prev_pos = None
history = []
ansi_escape = re.compile(r'\x1B\[[0-?]*[ -/]*[@-~]')


def update_adc(line):
    parts = line.replace("mV", "").split(":")
    if len(parts) == 2:
        idx = int(parts[0][3:]) - 1
        mv = int(parts[1].strip())
        if 0 <= idx < 4:
            adc_labels[idx].config(text=f"ADC{idx+1}: {mv} mV")
            adc_bars[idx]["value"] = mv


def draw_tiles():
    for cell in cells.values():
        cell.config(bg=COLOR_TILE, relief="raised")
    if current_pos and current_pos in cells:
        cells[current_pos].config(bg=COLOR_ACTIVE, relief="sunken")


def update_history(new_pos):
    global history, prev_pos
    if not new_pos or new_pos.lower() == "none":
        return
    if prev_pos and prev_pos.lower() != "none" and new_pos != prev_pos:
        history.append(prev_pos)
        if len(history) > HISTORY_MAX:
            history.pop(0)
    for i in range(HISTORY_MAX):
        if i < len(history):
            history_var[i].set(f"{i+1}. {history[-(i + 1)]}")
        else:
            history_var[i].set("---")


def save_last_position_sync():
    global history, current_pos
    if current_pos and current_pos.lower() != "none":
        if not history or history[-1] != current_pos:
            history.append(current_pos)
            if len(history) > HISTORY_MAX:
                history.pop(0)
        for i in range(HISTORY_MAX):
            if i < len(history):
                history_var[i].set(f"{i+1}. {history[-(i + 1)]}")
            else:
                history_var[i].set("---")


def read_serial():
    global buffer, current_pos, prev_pos, history
    try:
        ser = serial.Serial(PORT, BAUD, timeout=0.1)
    except serial.SerialException as e:
        print(f"Nie mogę otworzyć portu {PORT}: {e}")
        return

    partial_line = ""
    while True:
        try:
            data = ser.read(64)
            if not data:
                continue
            text = data.decode(errors="replace")

            # Twój oryginalny warunek czyszczenia terminala
            if "\033[2J\033[H\033[2J\033[H\033[2J\033[H\033[2J\033[H" in text:
                save_last_position_sync()
                buffer.clear()
                current_pos = None
                prev_pos = None
                pos_var.set("None")
                for cell in cells.values():
                    cell.config(bg=COLOR_TILE)
                for idx in range(4):
                    adc_labels[idx].config(text=f"ADC{idx+1}: --- mV")
                    adc_bars[idx]["value"] = 0

            partial_line += text
            while "\r" in partial_line:
                idx = partial_line.index("\r")
                line = partial_line[:idx]
                partial_line = partial_line[idx + 1:]
                line = ansi_escape.sub("", line).strip()
                if not line:
                    continue
                buffer.append(line)
                print(f"Odebrano: {line}")

                if line.startswith("ADC"):
                    root.after(0, update_adc, line)

                if "pos:" in line:
                    new_pos = line.split("pos:")[-1].strip()
                    if not new_pos or new_pos.lower() == "none":
                        current_pos = None
                        root.after(0, draw_tiles)
                        pos_var.set("None")
                        continue
                    if new_pos != current_pos:
                        prev_pos = current_pos
                        current_pos = new_pos
                        update_history(current_pos)
                        pos_var.set(current_pos)
                        root.after(0, draw_tiles)
        except Exception as e:
            print("Błąd w odczycie UART:", e)
            continue


threading.Thread(target=read_serial, daemon=True).start()
draw_tiles()
root.mainloop()

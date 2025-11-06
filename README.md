# Simulador de Viaje Espacial

> Proyecto académico en **C++** que modela un bucle de decisiones diarias para la tripulación de una nave espacial. Mantiene la lógica simple del archivo original (`ALGORITMOS.cpp`) con mejoras de legibilidad, validación de entradas y condición estricta de avance de día.

![status](https://img.shields.io/badge/status-Activo-success) ![lang](https://img.shields.io/badge/lang-C%2B%2B17-blue) ![os](https://img.shields.io/badge/OS-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)

---

## 🛰️ Resumen

El jugador asume el rol de capitán y, durante un número limitado de días, elige **explorar**, **reparar la nave**, **enviar señales** o **rendirse**. Cada decisión afecta los recursos de la nave (**combustible, oxígeno, suministros, integridad**) y, en ciertos casos, dispara **eventos aleatorios**.

**Regla clave:** _el día **solo avanza** cuando la acción del menú **se completa**._

---

## ✨ Características

- Menú diario simple (con validación robusta).
- Exploración con hallazgos/peligros **independientes** por probabilidad.
- Reparación proporcional a suministros (10 suministros → +1% integridad).
- Enviar señales con evento 50/50 (**ayuda** o **ataque**) y **noche** posterior.
- Noche con consumo fijo y **15%** de un único evento aleatorio (tormenta / alienígenas / meteoritos con decisión del jugador).
- Estado siempre “saturado” en [0, 100] para recursos e integridad.

---

## 🧩 Reglas de juego (resumen)

- **Explorar**: requiere `combustible ≥ 15`. Consume 15.
  - Oxígeno: 60% (+20..40)
  - Combustible: 25% (+10..30)
  - Suministros: 25% (+30..100)
  - Tormenta: 25% (−10%..−20% integridad)
  - Aterrizaje forzado: 25% (−10%..−20% integridad)

- **Reparar**: si `integridad = 100%` o `suministros < 10` → **no se completa**.
  - `reparar = min(porcentaje, 100 − integridad, suministros/10)`
  - Costo: `reparar * 10` suministros
  - Efecto: `integridad += reparar`

- **Enviar señales** → evento inmediato:
  - **Ayuda**: `+60 combustible` y `+30% integridad`
  - **Ataque**: `−15% integridad` y `−20 suministros`
  - **Noche** (solo aquí): `−20 oxígeno`, `−30 suministros` y **15%** de un **único** evento:
  - Tormenta cósmica: `−10 oxígeno`
  - Alienígenas: 50% amistoso (`+20 combustible`) / 50% hostil (`−10% integridad`)
  - Meteoritos: el jugador decide maniobrar (`−10..30 combustible`) o recibir impacto (`−15%..−25% integridad`).

- **Rendirse**: fin de partida inmediato (no avanza el día).

---

## 🗂️ Estructura del repositorio

```
.
├── ALGORITMOS.cpp                        # Código fuente principal (C++)
├── Analisis_y_Diseno_Simulador.drawio    # Diagrama de flujo (diagrams.net)
├── Analisis_y_Diseno_Simulador.pdf       # Documento de análisis y diseño (PDF)
├── Analisis_y_Diseno_Simulador.docx      # Documento editable (Word)
└── README.md                              # Este archivo
```

---

## 🛠️ Requisitos

- **Compilador C++17** o superior (GCC, Clang o MSVC).
- En **Windows**, consola en **UTF‑8** (el programa ya usa `SetConsoleOutputCP(CP_UTF8)`).
- No hay dependencias externas.

---

## ▶️ Compilación y ejecución

### Windows (MinGW / MSYS2)
```bash
g++ -std=c++17 -O2 -Wall -Wextra -o nave.exe ALGORITMOS.cpp
./nave.exe
```

### Linux / macOS
```bash
g++ -std=c++17 -O2 -Wall -Wextra -o nave ALGORITMOS.cpp
./nave
```

> Consejo: Se compila con `-O2 -Wall -Wextra` para obtener advertencias útiles.

---

## ⌨️ Entradas del usuario

| Entrada                | Tipo   | Cuándo se solicita                          |
|------------------------|--------|---------------------------------------------|
| Nombre del capitán     | string | Al inicio                                   |
| Opción del menú (1‑4)  | int    | Cada día                                    |
| % a reparar (1‑100)    | int    | Solo si eliges “Reparar”                    |
| Decisión meteoritos    | int    | Solo de noche tras “Enviar señales” (1/0)   |

**Regla de avance:** si la acción **no se completa** (por ejemplo, sin combustible para explorar o sin suministros para reparar), el **día no avanza**.

---

## 🔢 Variables principales

| Variable      | Tipo   | Rango        | Descripción                        |
|---------------|--------|--------------|------------------------------------|
| `combustible` | int    | 0..100       | Combustible disponible             |
| `oxigeno`     | int    | 0..100       | Oxígeno disponible                 |
| `suministros` | int    | 0..100       | Suministros de la nave             |
| `integridad`  | int    | 0..100 (%)   | Integridad estructural de la nave  |
| `dia`         | int    | 1..15        | Día actual                         |
| `Rendirse`    | bool   | —            | Bandera de fin de juego            |

---

## 🧪 Ejecución de ejemplo (fragmento)

```
===========================================
Día: 1
===========================================
1. Explorar un planeta
2. Reparar la nave
3. Enviar señales
4. Rendirse
Elige una opción (1-4): 1

Exploración del planeta iniciada...
¡Encontraste 34 unidades de oxígeno!
ALERTA: ¡Aterrizaje forzado! Daño: 14%
Estado actual de la nave:
    Combustible: 25
    Oxígeno    : 84
    Suministros: 40
    Integridad : 86%
```

---

## ⚙️ Parámetros que puedes ajustar rápido

En `ALGORITMOS.cpp`:
- **Probabilidades** (60%, 25%, 15%…) → busca `rand() % 100 < X`.
- **Rangos** de recursos/daños → busca expresiones como `rand() % 21 + 20`.
- **Consumo nocturno** → bloque “Noche en el espacio”.

---

## 📄 Licencia

Proyecto de uso académico. Puedes reutilizar citando la fuente del repositorio.

---

## 👤 Créditos

- Equipo del proyecto (1 persona para diseño y desarrollo).
- Ajustes de impresión, validación de entradas y documentación.
- Diagrama: `Analisis_y_Diseno_Simulador.drawio` (diagrams.net).

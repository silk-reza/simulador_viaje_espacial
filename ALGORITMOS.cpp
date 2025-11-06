// ============================================================
// Simulador sencillo de viaje espacial (versión comentada)
// - Mantiene la lógica original del equipo
// - Solo arregla impresión/entradas y condiciona avance del día
// - Comentarios puntuales (no en cada línea) para cumplir lineamientos
// ============================================================

#include <iostream>
#include <cmath>
#include <string>
#include <windows.h>   // Para configurar UTF-8 en consola de Windows
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <limits>      // Para limpiar el buffer de entrada con numeric_limits

using namespace std;

// -------------------------------
// Estado global del juego
// -------------------------------
string capitan;
int combustible = 30, oxigeno = 50, suministros = 40, integridad = 100, dia = 1;
bool Rendirse = false;
int tiempo = 14; // (No se usa en la lógica actual; se conserva por compatibilidad)
int opcion;      // Opción elegida en el menú

// Pide el nombre del capitán y da la bienvenida
void NombreCapitan() {
  cout << "Por favor, ingresa el nombre del capitán: ";
  getline(cin, capitan);
  if (capitan.empty()) capitan = "Sin-Nombre";
  cout << "Bienvenido, Capitán " << capitan << "!" << endl;
}

int main() {
  // Configura consola para mostrar tildes/ñ en Windows
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  srand(time(NULL));

  // Presentación
  cout << endl
       << "===========================================" << endl
       << "  ¡Bienvenido a la aventura espacial!" << endl
       << "===========================================" << endl
       << "Prepárate para comandar tu nave y enfrentarte a los peligros del espacio" << endl
       << endl;

  NombreCapitan();

  // Estado inicial, solo informativo
  cout << "Antes del despegue, la nave tiene " << suministros << " suministros disponibles." << endl;
  cout << "Antes del despegue, la nave tiene " << oxigeno     << " de oxígeno disponible."    << endl;
  cout << "Antes del despegue, la nave tiene " << combustible << " de combustible disponible."<< endl;
  cout << "Antes del despegue, la nave tiene " << integridad  << "% de integridad."          << endl;

  cout << endl << "Presiona Enter para continuar...";
  cin.get();

  // -------------------------------
  // Bucle principal: un intento por día
  // NOTA: El día solo avanza si la acción elegida se completa.
  // -------------------------------
  while (dia <= 15 && !Rendirse) {
    cout << endl
         << "===========================================" << endl
         << "Día: " << dia << endl
         << "===========================================" << endl;

    // Menú de acciones
    cout << "1. Explorar un planeta" << endl;
    cout << "2. Reparar la nave" << endl;
    cout << "3. Enviar señales" << endl;
    cout << "4. Rendirse" << endl;
    cout << "Elige una opción (1-4): ";

    // Validación de entrada numérica
    if (!(cin >> opcion)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Entrada inválida. Intenta de nuevo." << endl;
      continue; // Día NO avanza
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Por defecto, el día NO avanza a menos que la acción se complete
    bool accionValida = false;

    // Eco de opción elegida (mensajes claros)
    switch (opcion) {
      case 1:
        cout << "Escogiste explorar un planeta" << endl;
        break;
      case 2:
        cout << "Escogiste reparar la nave" << endl;
        break;
      case 3:
        cout << "Escogiste enviar señales" << endl;
        break;
      case 4:
        cout << "Escogiste rendirte" << endl;
        break;
      default:
        cout << "Opción inválida." << endl;
        continue; // Día NO avanza
    }

    // ====================================================
    // ACCIÓN 1: EXPLORAR UN PLANETA
    // - Requiere 15 de combustible
    // - Puede generar hallazgos/peligros de forma independiente
    // - Si no hay combustible suficiente, el día NO avanza
    // ====================================================
    if (opcion == 1) {
      cout << endl << "Exploración del planeta iniciada..." << endl;

      if (combustible < 15) {
        cout << "No tienes suficiente combustible para explorar." << endl;
        // Día NO avanza
      } else {
        combustible -= 15;

        // Hallazgos/peligros independientes
        if (rand() % 100 < 60) { // 60% oxígeno (20-40)
          int cantidad = rand() % 21 + 20;
          oxigeno += cantidad; if (oxigeno > 100) oxigeno = 100;
          cout << "¡Encontraste " << cantidad << " unidades de oxígeno!" << endl;
        }
        if (rand() % 100 < 25) { // 25% combustible (10-30)
          int cantidad = rand() % 21 + 10;
          combustible += cantidad; if (combustible > 100) combustible = 100;
          cout << "¡Encontraste " << cantidad << " unidades de combustible!" << endl;
        }
        if (rand() % 100 < 25) { // 25% suministros (30-100)
          int cantidad = rand() % 71 + 30;
          suministros += cantidad; if (suministros > 100) suministros = 100;
          cout << "¡Encontraste " << cantidad << " unidades de suministros!" << endl;
        }
        if (rand() % 100 < 25) { // 25% tormenta (daño 10-20%)
          int dano = rand() % 11 + 10;
          integridad -= dano; if (integridad < 0) integridad = 0;
          cout << "ALERTA: ¡Tormenta eléctrica! Daño: " << dano << "%" << endl;
        }
        if (rand() % 100 < 25) { // 25% aterrizaje forzado (daño 10-20%)
          int dano = rand() % 11 + 10;
          integridad -= dano; if (integridad < 0) integridad = 0;
          cout << "ALERTA: ¡Aterrizaje forzado! Daño: " << dano << "%" << endl;
        }
        if (integridad < 30) { // Advertencia de umbral bajo
          cout << "PELIGRO: Integridad crítica (" << integridad << "%)." << endl;
        }

        // Resumen rápido tras explorar
        cout << endl << "Estado actual de la nave:" << endl;
        cout << "    Combustible: " << combustible << endl;
        cout << "    Oxígeno    : " << oxigeno << endl;
        cout << "    Suministros: " << suministros << endl;
        cout << "    Integridad : " << integridad << "%" << endl;

        cout << endl << "Presiona Enter para intentar otra acción...";
        cin.get();

        accionValida = true; // Sí se pudo explorar
      }
    }

    // ====================================================
    // ACCIÓN 2: REPARAR LA NAVE
    // - No avanza el día si la integridad ya es 100% o no hay suministros
    // - 10 suministros reparan 1% de integridad
    // ====================================================
    if (opcion == 2) {
      cout << endl << "[Reparación de la nave]" << endl;

      if (integridad >= 100) {
        cout << "La nave ya está al 100% de integridad." << endl;
        // Día NO avanza
      } else {
        int porcentaje;
        cout << "¿Cuánto porcentaje deseas reparar? (1-100): ";
        if (!(cin >> porcentaje)) {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Entrada inválida." << endl;
        } else {
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          if (porcentaje < 1) porcentaje = 1;
          if (porcentaje > 100) porcentaje = 100;

          // Cálculo del máximo reparable por suministros y por integridad faltante
          int maxPosible    = suministros / 10;
          int maxIntegridad = 100 - integridad;
          int reparar = porcentaje;

          if (reparar > maxPosible)    reparar = maxPosible;
          if (reparar > maxIntegridad) reparar = maxIntegridad;

          if (reparar <= 0) {
            cout << "No tienes suministros suficientes para reparar." << endl;
          } else {
            suministros -= reparar * 10;
            integridad  += reparar;
            if (integridad > 100) integridad = 100;
            cout << "Se reparó la nave " << reparar << "% (costo: " << reparar * 10 << " suministros)." << endl;
            accionValida = true; // Sí se logró reparar algo
          }
        }
      }

      // Resumen rápido tras reparar
      cout << endl
           << "Estado actual -> "
           << "Combustible: " << combustible
           << " | Oxígeno: "  << oxigeno
           << " | Suministros: " << suministros
           << " | Integridad: " << integridad << "%" << endl;
    }

    // ====================================================
    // ACCIÓN 3: ENVIAR SEÑALES
    // - Siempre se completa (el día avanza)
    // - Después ocurre la "noche" con consumo y posible evento (15%)
    // ====================================================
    if (opcion == 3) {
      cout << endl << "Enviando señales al espacio..." << endl;

      int evento = rand() % 2; // 0 = ayuda, 1 = ataque
      if (evento == 0) {
        cout << "¡Recibiste ayuda! (+60 combustible, +30% integridad)" << endl;
        combustible += 60; if (combustible > 100) combustible = 100;
        integridad  += 30; if (integridad  > 100) integridad  = 100;
      } else {
        cout << "ALERTA: ¡Ataque extraterrestre! (-15% integridad, -20 suministros)" << endl;
        integridad -= 15; if (integridad < 0) integridad = 0;
        suministros -= 20; if (suministros < 0) suministros = 0;
      }

      // -------- Noche en el espacio --------
      cout << endl << "Noche en el espacio..." << endl;
      // Consumo nocturno fijo
      oxigeno -= 20;     if (oxigeno < 0) oxigeno = 0;
      suministros -= 30; if (suministros < 0) suministros = 0;
      cout << "Consumo nocturno: -20 oxígeno, -30 suministros" << endl;

      // 15% de probabilidad de un único evento nocturno
      int probabilidad = rand() % 100;
      if (probabilidad < 15) {
        int tipoEvento = rand() % 3; // 0: tormenta, 1: alienígenas, 2: meteoritos
        if (tipoEvento == 0) {
          int perdida = 10; // PDF: -10 oxígeno (valor fijo)
          oxigeno -= perdida; if (oxigeno < 0) oxigeno = 0;
          cout << "ALERTA: Tormenta cósmica ( -" << perdida << " oxígeno )" << endl;
        } else if (tipoEvento == 1) {
          int tipoAlien = rand() % 2; // 0 amistoso / 1 hostil
          if (tipoAlien == 0) {
            cout << "Encuentro alienígena amistoso (+20 combustible)" << endl;
            combustible += 20; if (combustible > 100) combustible = 100;
          } else {
            int perdida = static_cast<int>(integridad * 0.10);
            integridad -= perdida; if (integridad < 0) integridad = 0;
            cout << "Encuentro alienígena agresivo ( -" << perdida << "% integridad )" << endl;
          }
        } else {
          // Decisión del jugador en meteoritos
          cout << "ALERTA: Meteoritos detectados. ¿Maniobrar para esquivarlos? (1 = Sí, 0 = No): ";
          int decision = 0;
          if (!(cin >> decision)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            decision = 0; // Si no se puede leer, por defecto no maniobra
          } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
          }

          if (decision == 1) {
            int gasto = rand() % 21 + 10; // 10-30 combustible
            combustible -= gasto; if (combustible < 0) combustible = 0;
            cout << "Maniobra realizada ( -" << gasto << " combustible )" << endl;
          } else {
            int dano = rand() % 11 + 15;  // 15-25% de integridad
            integridad -= dano; if (integridad < 0) integridad = 0;
            cout << "Impacto recibido ( -" << dano << "% integridad )" << endl;
          }
        }
      } else {
        cout << "No ocurrió ningún evento especial esta noche." << endl;
      }

      // Resumen tras la noche
      cout << endl << "Estado actual de la nave:" << endl;
      cout << "   Combustible: " << combustible << endl;
      cout << "   Oxígeno    : " << oxigeno << endl;
      cout << "   Suministros: " << suministros << endl;
      cout << "   Integridad : " << integridad << "%" << endl;

      cout << endl << "Presiona Enter para continuar...";
      cin.get();

      accionValida = true; // Enviar señales siempre se completa
    }

    // ====================================================
    // ACCIÓN 4: RENDIRSE (termina la partida sin avanzar día)
    // ====================================================
    if (opcion == 4) {
      cout << endl << "Has decidido rendirte. La misión termina aquí." << endl;
      Rendirse = true; // Día NO avanza
    }

    // Avance de día condicionado (= solo si la acción se completó)
    if (accionValida) {
      dia++;
    } else if (!Rendirse) {
      cout << endl << "[El día NO avanza porque la acción no se pudo completar.]" << endl;
    }
  }

  return 0;
}

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

using namespace std;

void menu();
void limpiarPantalla();

void ingresarProductos(string productos[], float precios[], bool &datos);
void mostrarProductos(string productos[], float precios[], bool datos);
int seleccionarProducto(string productos[], float precios[], bool datos);

void buscarProducto(string productos[], float precios[], bool datos);

void comprarProducto(string productos[], float precios[], bool datos,
					 string &productoCompra, float &precioCompra,
					 int &cantidad, float &total,
					 string &metodoPago, float &recibido,
					 float &vuelto, bool &compraRealizada);

void ticket(string productoCompra, float precioCompra,
			int cantidad, float total,
			string metodoPago, float recibido,
			float vuelto, bool compraRealizada);

void eliminarProducto(string productos[], float precios[], bool &datos);

int main()
{
	string productos[5];
	float precios[5];
	
	bool datos = false;
	bool compraRealizada = false;
	
	string productoCompra = "";
	string metodoPago = "";
	
	float precioCompra = 0;
	float total = 0;
	float recibido = 0;
	float vuelto = 0;
	
	int cantidad = 0;
	int opcion;
	
	do
	{
		menu();
		cin >> opcion;
		
		limpiarPantalla();
		
		switch(opcion)
		{
		case 1:
			ingresarProductos(productos, precios, datos);
			break;
			
		case 2:
			mostrarProductos(productos, precios, datos);
			break;
			
		case 3:
			buscarProducto(productos, precios, datos);
			break;
			
		case 4:
			comprarProducto(productos, precios, datos,
							productoCompra, precioCompra,
							cantidad, total,
							metodoPago, recibido,
							vuelto, compraRealizada);
			break;
			
		case 5:
			ticket(productoCompra, precioCompra,
				   cantidad, total,
				   metodoPago, recibido,
				   vuelto, compraRealizada);
			break;
			
		case 6:
			eliminarProducto(productos, precios, datos);
			break;
			
		case 7:
			cout << "Gracias por utilizar el sistema libreria.\n";
			break;
			
		default:
			cout << "Opcion invalida.\n";
		}
		
		if(opcion != 7)
		{
			cout << endl;
			system("pause");
			limpiarPantalla();
		}
		
	}while(opcion != 7);
	
	return 0;
}

void menu()
{
	cout << "=====================================\n";
	cout << "       SISTEMA LIBRERIA SARITA		\n";
	cout << "=====================================\n";
	cout << "1. Ingresar Producto\n";
	cout << "2. Mostrar Producto\n";
	cout << "3. Buscar Producto\n";
	cout << "4. Comprar Producto\n";
	cout << "5. Ticket de Producto\n";
	cout << "6. Eliminar Producto\n";
	cout << "7. Salir\n";
	cout << "Seleccione opcion: ";
}

void limpiarPantalla()
{
	system("cls");
}

void ingresarProductos(string productos[], float precios[], bool &datos)
{
	if(datos)
	{
		cout << "Ya existen productos ingresados.\n";
		return;
	}
	
	cout << "===== INGRESO DE PRODUCTOS =====\n";
	
	for(int i=0;i<5;i++)
	{
		cout << "\nProducto " << i+1 << ": ";
		cin.ignore();
		getline(cin, productos[i]);
		
		do
		{
			cout << "Precio Q: ";
			cin >> precios[i];
			
			if(cin.fail() || precios[i] <= 0)
			{
				cout << "Precio invalido. Ingrese un numero correcto.\n";
				
				cin.clear();
				cin.ignore(1000, '\n');
			}
			
		}while(precios[i] <= 0);
	}
	
	datos = true;
	cout << "\nProductos guardados correctamente.\n";
}

void mostrarProductos(string productos[], float precios[], bool datos)
{
	if(!datos)
	{
		cout << "No existen productos registrados.\n";
		return;
	}
	
	cout << fixed << setprecision(2);
	
	cout << "===============================\n";
	cout << " No   Producto        Precio\n";
	cout << "===============================\n";
	
	for(int i=0;i<5;i++)
	{
		if(productos[i] != "")
		{
			cout << " " << i+1 << "    "
			<< productos[i] << "        Q"
			<< precios[i] << endl;
		}
	}
	
}

int seleccionarProducto(string productos[], float precios[], bool datos)
{
	if(!datos)
	{
		cout << "No hay productos disponibles.\n";
		return -1;
	}
	
	int opcion;
	
	mostrarProductos(productos, precios, datos);
	
	cout << "\nSeleccione producto: ";
	cin >> opcion;
	
	if(opcion < 1 || opcion > 5 || productos[opcion-1] == "")
	{
		cout << "Producto invalido.\n";
		return -1;
	}
	
	return opcion-1;
}

void buscarProducto(string productos[], float precios[], bool datos)
{
	if(!datos)
	{
		cout << "No hay productos registrados.\n";
		return;
	}
	
	string nombre;
	
	cout << "Ingrese nombre del producto: ";
	cin.ignore();
	getline(cin, nombre);
	
	for(int i=0;i<5;i++)
	{
		if(productos[i] == nombre)
		{
			cout << "\nProducto encontrado.\n";
			cout << "Nombre: " << productos[i] << endl;
			cout << "Precio: Q" << precios[i] << endl;
			return;
		}
	}
	
	cout << "Producto no encontrado.\n";
}

void comprarProducto(string productos[], float precios[], bool datos,
					 string &productoCompra, float &precioCompra,
					 int &cantidad, float &total,
					 string &metodoPago, float &recibido,
					 float &vuelto, bool &compraRealizada)
{
	int pos = seleccionarProducto(productos, precios, datos);
	
	if(pos == -1)
		return;
	
	do
	{
		cout << "Cantidad: ";
		cin >> cantidad;
		
		if(cantidad <= 0)
			cout << "Cantidad invalida.\n";
		
	}while(cantidad <= 0);
	
	productoCompra = productos[pos];
	precioCompra = precios[pos];
	total = precioCompra * cantidad;
	
	int pago;
	
	cout << "\n1. Efectivo\n";
	cout << "2. Tarjeta\n";
	cout << "Seleccione metodo de pago: ";
	cin >> pago;
	
	if(pago == 1)
	{
		metodoPago = "Efectivo";
		
		do
		{
			cout << "Dinero recibido Q: ";
			cin >> recibido;
			
			if(recibido < total)
				cout << "Dinero insuficiente.\n";
			
		}while(recibido < total);
		
		vuelto = recibido - total;
	}
	else if(pago == 2)
	{
		metodoPago = "Tarjeta";
		recibido = total;
		vuelto = 0;
	}
	else
	{
		cout << "Metodo incorrecto.\n";
		return;
	}
	
	compraRealizada = true;
	
	cout << "\nCompra realizada correctamente.\n";
}

void ticket(string productoCompra, float precioCompra,
			int cantidad, float total,
			string metodoPago, float recibido,
			float vuelto, bool compraRealizada)
{
	if(!compraRealizada)
	{
		cout << "No existe una compra realizada.\n";
		return;
	}
	
	cout << fixed << setprecision(2);
	
	cout << "\n==================================\n";
	cout << "        TICKET LIBRERIA SARITA\n";
	cout << "====================================\n";
	cout << "Producto: " << productoCompra << endl;
	cout << "Precio: Q" << precioCompra << endl;
	cout << "Cantidad: " << cantidad << endl;
	cout << "Total: Q" << total << endl;
	cout << "Metodo pago: " << metodoPago << endl;
	cout << "Recibido: Q" << recibido << endl;
	cout << "Vuelto: Q" << vuelto << endl;
}

void eliminarProducto(string productos[], float precios[], bool &datos)
{
	if(!datos)
	{
		cout << "No existen productos.\n";
		return;
	}
	
	mostrarProductos(productos, precios, datos);
	
	int opcion;
	
	cout << "\n0. Eliminar todos\n";
	cout << "Seleccione producto a eliminar: ";
	cin >> opcion;
	
	if(opcion == 0)
	{
		for(int i=0;i<5;i++)
		{
			productos[i]="";
			precios[i]=0;
		}
		
		datos=false;
		cout << "Todos los productos eliminados.\n";
	}
	else if(opcion>=1 && opcion<=5 && productos[opcion-1]!="")
	{
		cout << "Producto eliminado: " << productos[opcion-1] << endl;
		
		productos[opcion-1]="";
		precios[opcion-1]=0;
	}
	else
	{
		cout << "Opcion invalida.\n";
	}
}

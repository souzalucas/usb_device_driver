#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

// Eh chamada quando o dispositivo for conectado
static int dispositivo_conectado(struct usb_interface *interface, const struct usb_device_id *id) {
  printk(KERN_INFO "[*] Dispositivo (%04X:%04X) conectado\n", id->idVendor, id->idProduct);
  return 0;
}

// Eh chamada quando o dispositivo for desconectado
static void dispositivo_desconectado(struct usb_interface *interface) {
  printk(KERN_INFO "[*] Dispositivo desconectado\n");
}

// usb_device_id
static struct usb_device_id tabela_do_dispositivo[] = {
  // 13fd:3920
  { USB_DEVICE(0x13fd, 0x3920) },     // Informacao obtida atraves do comando "lsusb"
  {} /* Finalizando a entrada */
};
MODULE_DEVICE_TABLE (usb, tabela_do_dispositivo);

// usb_driver
static struct usb_driver driver_do_dispositivo = {
  .name = "Identificador de Dispositivo USB v1.0",
  .id_table = tabela_do_dispositivo,
  .probe = dispositivo_conectado,
  .disconnect = dispositivo_desconectado
};

static int __init modulo_init(void) {
  int ret = -1;
  printk(KERN_INFO "Registrando driver no kernel");
  ret = usb_register(&driver_do_dispositivo);
  printk(KERN_INFO "\tDriver registrado com sucesso");
  return ret;
}

static void __exit modulo_exit(void) {
  printk(KERN_INFO "Removendo driver no kernel");
  usb_deregister(&driver_do_dispositivo);
  printk(KERN_INFO "\tDriver Removido com sucesso");
}

module_init(modulo_init);
module_exit(modulo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lucas Souza Santos");
MODULE_DESCRIPTION("Este driver reconhece um dispositivo USB específico quando é conectado");
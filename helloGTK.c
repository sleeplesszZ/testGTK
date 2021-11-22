#include <gtk/gtk.h>

//加载图片
GdkPixbuf *create_pixbuf(const gchar * filename)
{
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if (!pixbuf)
    {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }

    return pixbuf;
}

//按钮响应
void OnButton(GtkWidget *widget, gpointer window)
{
    printf("button clicked\n");
}

//添加菜单
void AddMenu(GtkWidget *vbox)
{
    GtkWidget *menu = gtk_menu_new();
    GtkWidget *menuitem = gtk_menu_item_new_with_label("新建");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);
    menuitem = gtk_menu_item_new_with_label("打开");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);
    menuitem = gtk_menu_item_new_with_label("保存");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);

    GtkWidget *rootmenu = gtk_menu_item_new_with_label(" 文件 ");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu), menu);

    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), rootmenu);

    //
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
}

//
int main(int argc, char *argv[])
{
    //声明一个窗口构件
    GtkWidget *window;

    //初始化GTK++
    gtk_init(&argc, &argv);

    //创建主窗口
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "GTK窗口");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    // gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    //add icon
    GdkPixbuf *icon = create_pixbuf("demo.png");
    gtk_window_set_icon(GTK_WINDOW(window), icon);

    //button
    GtkWidget *button1 = gtk_button_new(); //空按钮
    gtk_widget_set_tooltip_text(button1, "im button one");


    GtkWidget *button2 = gtk_button_new_with_label("按钮2"); //带文本按钮
    gtk_widget_set_tooltip_text(button2, "gtk_button_new_with_label");
    g_signal_connect(GTK_BUTTON(button2), "clicked", G_CALLBACK(OnButton), NULL);
    
    GtkWidget *button3 = gtk_button_new_with_mnemonic("_Button");
    gtk_widget_set_tooltip_text(button3, "gtk_button_new_with_mnemonic");
    g_signal_connect(GTK_BUTTON(button3), "clicked", G_CALLBACK(OnButton), NULL);

    //创建居中对齐
    GtkWidget *align = gtk_alignment_new(1, 1, 0, 0);//Alignment构件只能添加一个子构件
    gtk_container_add(GTK_CONTAINER(align), button3);
    // gtk_container_add(GTK_CONTAINER(window), align);

    //GtkHBox可以将它的子构件横向排列，GtkVBox可以将它的子构件纵向排列
    //gtk_vbox_new(gboolean homogeneous, gint spacing) 
    //@homogeneous 为TRUE时，强制盒中的构件都占用相同大小的空间
    //@spacing 以像素为单位设置的构件之间的间距
    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    AddMenu(vbox);

    //将窗口的destroy消息绑定处理函数gtk_main_quit
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // gtk_widget_show(align);
    // gtk_widget_show(button2);
    //显示主窗口
    gtk_widget_show_all(window);
    g_object_unref(icon);

    //进入GTK+循环
    gtk_main();

    return 0;
}

// -pthread 
// -I/usr/include/gtk-2.0 
// -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include 
// -I/usr/include/gio-unix-2.0/ 
// -I/usr/include/cairo 
// -I/usr/include/pango-1.0 
// -I/usr/include/atk-1.0 
// -I/usr/include/cairo 
// -I/usr/include/pixman-1 
// -I/usr/include/libpng16 
// -I/usr/include/gdk-pixbuf-2.0 
// -I/usr/include/libpng16 
// -I/usr/include/pango-1.0 
// -I/usr/include/harfbuzz 
// -I/usr/include/pango-1.0 
// -I/usr/include/glib-2.0 
// -I/usr/lib/x86_64-linux-gnu/glib-2.0/include 
// -I/usr/include/freetype2 
// -lgtk-x11-2.0 
// -lgdk-x11-2.0 
// -lpangocairo-1.0 
// -latk-1.0 
// -lcairo 
// -lgdk_pixbuf-2.0 
// -lgio-2.0 
// -lpangoft2-1.0 
// -lpango-1.0 
// -lgobject-2.0 
// -lglib-2.0 
// -lfontconfig 
// -lfreetyp
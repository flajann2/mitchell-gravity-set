#[macro_use] extern crate conrod;
mod support;

fn main() {
    println!("MGS -- launched");
    feature::main();
}

mod feature {
    extern crate find_folder;
    extern crate piston_window;
    use conrod;
    use support;

    use self::piston_window::{PistonWindow, UpdateEvent, Window, WindowSettings};
    use self::piston_window::{Flip, G2d, G2dTexture, Texture, TextureSettings};
    use self::piston_window::OpenGL;
    use self::piston_window::texture::UpdateTexture;

    pub fn main() {
        const WIDTH: u32 = support::WIN_W;
        const HEIGHT: u32 = support::WIN_H;

        // Construct the window.
        let mut window: PistonWindow =
            WindowSettings::new("All Widgets - Piston Backend", [WIDTH, HEIGHT])
            .opengl(OpenGL::V3_2) // If not working, try `OpenGL::V2_1`.
            .samples(4)
            .exit_on_esc(true)
            .vsync(true)
            .build()
            .unwrap();

        let mut ui = conrod::UiBuilder::new([WIDTH as f64, HEIGHT as f64])
            .theme(support::theme())
            .build();

        let assets = find_folder::Search::KidsThenParents(3, 5).for_folder("assets").unwrap();
        let font_path = assets.join("fonts/NotoSans/NotoSans-Regular.ttf");
        ui.fonts.insert_from_file(font_path).unwrap();

        while let Some(event) = window.next(){
        }
    }
}

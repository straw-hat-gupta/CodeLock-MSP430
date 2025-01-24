# Keypad Door Lock System

## The Story

Initially, I wanted to make something cool with a microcontroller I had lying around. I wanted to challenge myself to build something from start to finish—something practical and not just another random project collecting dust. Then one day, I got locked out of my apartment, and none of my roommates were around. That’s when I had the idea of making a simple keypad door lock.  

One thing I wanted to make sure of was that I didn’t have to drill any holes in the door to affix the mechanism to the door.

And so, this is what I came up with.

---

## Demo

Here’s a quick demo of the project in action:

![name](https://github.com/user-attachments/assets/f0fcc957-7ee8-4496-b690-2d448bb9f368)

---
## The Tech Stack

### Hardware
- **MSP430 Microcontroller**: The brain of the system.
- **Input Buttons**: For passcode input.
- **7-Segment Display**: Provides real-time feedback for the user.
- **Relay and Servo Motor**: Control the physical locking mechanism.
- **Custom 3D-Printed/Laser-Cut Parts**: Designed to interface with the existing door lock without any additional fittings to affix it to the door.

### Software
- **C Programming**: Code to control the microcontroller, handle input, and manage the locking mechanism, as well as the logic for a keypad.
- **CAD Software (OnShape)**: For designing the locking/unlocking mechanism.
---
## Key Features

### 1. **Passcode Verification**
   - Enter a 4-digit passcode to unlock the door.
   - If the passcode matches the default (or the updated passcode), the door unlocks.
   - The system automatically locks again after a short delay.

### 2. **Customizable Passcode**
   - You can easily update the passcode via the keypad.
   - This adds an extra layer of security and makes it flexible for multiple users.

### 3. **Clear Screen Button**
   - Oops! Entered the wrong passcode? No worries—just press the clear button to reset and start over.

### 4. **Real-Time Feedback**
   - A **7-segment display** shows the entered digits as you type, so you always know what you’re inputting.

### 5. **Relay-Controlled Locking Mechanism**
   - The system integrates with a relay to trigger the locking mechanism.
   - When the correct passcode is entered, the relay activates a servo motor to unlock the door.

### 6. **DIY Keypad Using Switch Buttons**
   - I didn’t use a 4x4 keypad—because that would’ve been too easy! *(The real reason? I didn’t have one.)*
   - What I did have was a bunch of switch buttons that came with the kit, so instead of buying a keypad, I challenged myself to program one using these buttons.
   - This was harder than expected because the only wiring option I had was a breadboard from the kit. Debugging and ensuring all connections were properly made turned out to be quite the challenge, but it was incredibly satisfying to get it working.

### 7. **CAD-Designed Locking Mechanism**
   - The physical locking mechanism is custom-designed using CAD software and fabricated with 3D printing.
   - It’s tailored to fit most doors and ensures a smooth, reliable locking/unlocking action.

## What I Learned from This Project

Working on this project taught me a lot about hardware, fabrication, and coding. It wasn’t just about building something useful—it was about overcoming challenges and learning from them along the way. Here are some key lessons:

### 1. **Modeling Real Environments in CAD**
   - One of the biggest challenges was accurately modeling real-world objects in a CAD environment. Measurements in the real world don’t always translate perfectly to CAD.
   - The key takeaway? **Measure twice, test print, and measure again.** Your model is only as good as your measurements. A lot of time was saved once I realized this and started iterating quickly based on test prints.

### 2. **Best Practices for 3D Printing**
   - Designing the baseplate, which attaches to the door, was tricky because it needed tight tolerances to fit between existing door lock components without interfering with their functionality.
   - I learned how to design with 3D printing in mind—adjusting tolerances and understanding how to make parts fit snugly without breaking or jamming.

### 3. **Adapting Your Plan**
   - Originally, I thought I’d 3D print every single component of the design. I spent time carefully designing everything in CAD, only to realize this approach would take forever to test and prototype.
   - Instead, I pivoted to a **mixed fabrication approach**:
     - **3D Printing**: Used for the baseplate because it required variable thicknesses for structural support and to fit between the door lock components.
     - **Wooden Dowels**: Replaced 3D-printed pegs, as they were faster to prototype and could be sanded to the perfect diameter.
     - **Laser Cutting**: Used for the top plate and gears. Laser cutting was much faster and let me prototype components out of a single sheet of plastic.

### 4. **Programming Different Microprocessors**
   - I had experience working in C from past courses and as well as my past internship. But it was my first time with the MSP430 board. Understanding its documentation and figuring out how the different registers mapped to hardware behavior was intimidating.
   - However, once I understood how the registers worked, it became much easier and very satisfying to directly control the hardware by setting specific values. Seeing the results in real time—like the servo moving or the 7-segment display updating—was incredibly rewarding.

### 5. **Code Meets Hardware**
   - This project showed me the joy of working on something where **code directly interacts with hardware**. Watching the system come together and seeing how software and hardware complemented each other was one of the most rewarding parts of the entire process.


## How It Works

1. **Input the Passcode**  
   Type in the 4-digit passcode using the keypad. The digits appear on the 7-segment display.

2. **Unlock the Door**  
   If the passcode matches, the relay activates the servo, unlocking the door.

3. **Lock the Door**  
   After a short delay, the servo resets, locking the door again.

4. **Customizing the Passcode**  
   Use the keypad to change the default passcode whenever needed.

---


## CAD Designs and Fabrication

### CAD Designs
Here are some of the designs created in CAD to build the locking mechanism:
![CAD Design](assets/cad-design.png)

### Fabrication
This is what the fabricated parts looked like after 3D printing and laser cutting:
![Fabricated Parts](assets/fabricated-parts.png)

## What’s Next?

I’ve built the electronic system and programmed it to handle passcodes, clear button functionality, and lock/unlock operations. However, there are still a few improvements and enhancements I’d like to make:

1. **Create an Enclosure for the Components**  
   - Design and fabricate an enclosure to house all the components, including the keypad, display, and microcontroller.
   - Ensure the enclosure is compact, easy to mount, and protects the internal components.

2. **Switch to Battery Power**  
   - Convert the system to run on battery power instead of being powered through a wall-plug supply on a breadboard.
   - Use a low-power design to maximize battery life.

3. **Add Touchless Functionality**  
   - Implement an alternative unlocking method such as using an NFC tag.
   - Allow users to unlock the door by tapping a registered NFC tag to the device, providing convenience alongside the keypad.





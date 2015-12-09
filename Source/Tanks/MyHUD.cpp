// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanks.h"
#include "MyHUD.h"

#define BUTTONTYPE_MAIN_RESTART 	1
#define BUTTONTYPE_MAIN_EXIT 		2

#define BUTTONTYPE_CONFIRM_YES 	1
#define BUTTONTYPE_CONFIRM_NO 	2

#define CANVAS_WHITE if(Canvas) Canvas->SetDrawColor(FColor_White);


const FColor AMyHUD::FColorBlack = FColor(0, 0, 0, 255);
const FColor AMyHUD::FColorRed = FColor(255, 0, 0, 255);
const FColor AMyHUD::FColorYellow = FColor(255, 255, 0, 255);
const FColor AMyHUD::FColorBlue = FColor(0, 0, 255, 255);
const FColor AMyHUD::FColor_White = FColor(255, 255, 255, 255);

const FLinearColor AMyHUD::LC_Black = FLinearColor(0, 0, 0, 1);
const FLinearColor AMyHUD::LC_Pink = FLinearColor(1, 0, 1, 1);
const FLinearColor AMyHUD::LC_Red = FLinearColor(1, 0, 0, 1);
const FLinearColor AMyHUD::LC_Yellow = FLinearColor(1, 1, 0, 1);

AMyHUD::AMyHUD(const class FObjectInitializer& PCIP) : Super(PCIP)
{
    //Draw HUD?
    DontDrawHUD = false;
    
    //States
    ConfirmDialogOpen = false;
    InMainMenu = true;
    
    //Scale
    GlobalHUDMult = 1;
    DefaultFontScale = 0.7;   //scaling down a size 36 font
    
    //	I recommend creating fonts at a high resolution / size like 36
    //	then you can scale down the font as needed to any size of your choice
    // this avoids needing to make multiple fonts for different sizes, but have a high
    // resolution when you use larger font sizes
    
}


// Draw Dialogs
void AMyHUD::DrawHUD_DrawDialogs()
{
    DrawMainMenuButtons();
    if (ConfirmDialogOpen) DrawConfirm();
}

void AMyHUD::DrawConfirm()
{
    //Blue rect with alpha 50%
    DrawHUDRect(Canvas->SizeX / 2 - 90, Canvas->SizeY / 2 - 50, 200, 100, FLinearColor(0, 0, 1, 0.2333));
    
    //Draw buttons
    DrawConfirmButtons();
}

//Buttons
void AMyHUD::DrawMainMenuButtons()
{
    //Start Point
    float xStart = 100;
    float yStart = 410;
    
    //Background
    VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColor(255, 255, 255, 120)); //alpha 120/255
    
    //Text
    DrawHUDText(
                VerdanaFont, "Restart", xStart + 20, yStart + 20,
                LC_Black, DefaultFontScale,
                true, LC_Yellow
                );
    
    //Clear buttons with ButtonsMain.Empty()
    if (ButtonsMain.Num() < 1)
    {
        FHUDButtonStruct newButton = FHUDButtonStruct();
        newButton.type = BUTTONTYPE_MAIN_RESTART;
        newButton.toolTip = "Restart the Game!";
        newButton.minX = xStart;
        newButton.maxX = xStart + 150;
        newButton.minY = yStart;
        newButton.maxY = yStart + 80;
        
        //Add to correct array
        ButtonsMain.Add(newButton);
    }
    
    
    xStart = 100;
    yStart = 510;
    
    VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColor(255, 255, 255, 120)); //alpha 120/255
    
    //Text
    DrawHUDText(
                VerdanaFont, "Exit", xStart + 45, yStart + 20,
                LC_Black, DefaultFontScale,
                true, LC_Yellow
                );
    
    if (ButtonsMain.Num() < 2)
    {
        FHUDButtonStruct newButton = FHUDButtonStruct();
        newButton.type = BUTTONTYPE_MAIN_EXIT;
        newButton.toolTip = "Exit the Game!";
        newButton.minX = xStart;
        newButton.maxX = xStart + 150;
        newButton.minY = yStart;
        newButton.maxY = yStart + 80;
        
        //Add to correct array
        ButtonsMain.Add(newButton);
    }
}
void AMyHUD::DrawConfirmButtons()
{
    float xStart = Canvas->SizeX / 2 - 100;
    float yStart = Canvas->SizeY / 2 - 40;
    
    //Highlighted?
    if (ActiveButton_Type == BUTTONTYPE_CONFIRM_YES) ColorPtr = &LC_Red;
    else ColorPtr = &LC_Yellow;
    
    //Text
    DrawHUDText(
                VerdanaFont, "Yes", xStart + 30, yStart + 20,
                *ColorPtr, DefaultFontScale,
                true
                );
    
    if (ButtonsConfirm.Num() < 1)
    {
        FHUDButtonStruct newButton = FHUDButtonStruct();
        newButton.type = BUTTONTYPE_CONFIRM_YES;
        newButton.toolTip = "";
        newButton.minX = xStart;
        newButton.maxX = xStart + 75;
        newButton.minY = yStart + 20;
        newButton.maxY = yStart + 60;
        
        //Add to correct array
        ButtonsConfirm.Add(newButton);
    }
    
    xStart = Canvas->SizeX / 2 + 20;
    yStart = Canvas->SizeY / 2 - 40;
    
    //Highlighted?
    if (ActiveButton_Type == BUTTONTYPE_CONFIRM_NO) ColorPtr = &LC_Red;
    else ColorPtr = &LC_Yellow;
    
    //Text
    DrawHUDText(
                VerdanaFont, "No", xStart + 30, yStart + 20,
                *ColorPtr, DefaultFontScale,
                true
                );
    
    if (ButtonsConfirm.Num() < 2)
    {
        FHUDButtonStruct newButton = FHUDButtonStruct();
        newButton.type = BUTTONTYPE_CONFIRM_NO;
        newButton.toolTip = "";
        newButton.minX = xStart;
        newButton.maxX = xStart + 75;
        newButton.minY = yStart + 20;
        newButton.maxY = yStart + 60;
        
        //Add to correct array
        ButtonsConfirm.Add(newButton);
    }
}

void AMyHUD::DrawHealthBar()
{
    DrawHUDText(
                VerdanaFont, "Health", 100, 50,
                FColor_White, DefaultFontScale,
                true
                );
    
    //Goes from left to right
    DrawHUDRect(100, 100, 50, 50, FLinearColor(0, 1, 0, 1));
    DrawHUDRect(150, 100, 50, 50, FLinearColor(0, 1, 0, 1));
    DrawHUDRect(200, 100, 50, 50, FLinearColor(0, 1, 0, 1));
    DrawHUDRect(250, 100, 50, 50, FLinearColor(0, 1, 0, 1));
    DrawHUDRect(300, 100, 50, 50, FLinearColor(0, 1, 0, 1));
}

// Is cursor in Buttons
int32 AMyHUD::CheckCursorInButton(const TArray<FHUDButtonStruct>& ButtonArray)
{
    for (int32 b = 0; b < ButtonArray.Num(); b++)
    {
        CurCheckButton = &ButtonArray[b];
        
        //check cursor in bounds
        if (CurCheckButton->minX <= MouseLocation.X && MouseLocation.X <= CurCheckButton->maxX &&
            CurCheckButton->minY <= MouseLocation.Y && MouseLocation.Y <= CurCheckButton->maxY)
        {
            
            //Active Button Type
            ActiveButton_Type = CurCheckButton->type;
            
            //Tool Tip
            ActiveButton_Tip = CurCheckButton->toolTip;
            
            //Mouse Clicked?
            if (ThePC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
            {
                return ActiveButton_Type;
            }
        }
    }
    
    //No Click Occurred This Tick
    return -1;
}

//Check Confirm
void AMyHUD::CheckCursorInButtonsConfirm()
{
    //Check Confirm Buttons
    ClickedButtonType = CheckCursorInButton(ButtonsConfirm); //fills global ActiveButton_Type
    
    if (ClickedButtonType == BUTTONTYPE_CONFIRM_YES)
    {
        ThePC->ConsoleCommand("Exit");
        return;
    }
    if (ClickedButtonType == BUTTONTYPE_CONFIRM_NO)
    {
        ConfirmDialogOpen = false;
        ButtonsConfirm.Empty(); //Buttons not needed anymore
        return;
    }
}

//Check Buttons
void AMyHUD::CheckCursorInButtonsMain()
{
    //Check Confirm Buttons
    ClickedButtonType = CheckCursorInButton(ButtonsMain);
    
    if (ClickedButtonType == BUTTONTYPE_MAIN_RESTART)
    {
        ThePC->ConsoleCommand("RestartLevel");
        return;
    }
    if (ClickedButtonType == BUTTONTYPE_MAIN_EXIT)
    {
        ConfirmDialogOpen = true;
        return;
    }
}
void AMyHUD::DrawHUD_CheckCursorInButtons()
{
    if (ConfirmDialogOpen)
    {
        CheckCursorInButtonsConfirm();
        
        return;
    }
    
    CheckCursorInButtonsMain();
}

void AMyHUD::DrawToolTip()
{
    float xStart = MouseLocation.X + 150;
    float yStart = MouseLocation.Y + 5;
    
    //out vars
    float RV_xLength;
    float RV_yLength;
    
    //Text Size
    GetTextSize(
                ActiveButton_Tip,
                RV_xLength,
                RV_yLength,
                UE4Font,
                DefaultFontScale
                );
    
    
    if (xStart + RV_xLength >= Canvas->SizeX - 40)
    {
        xStart -= 150 + 140 + 64 + RV_xLength;
        
        if (xStart < 33) xStart = 33;
    }
    
    //Background
    DrawHUDRect(
                xStart, yStart,
                RV_xLength + 70,
                80,
                FLinearColor(0, 0, 1, 0.7) //alpha 0.7
                );
    
    //Tool Tip
    DrawText(
             ActiveButton_Tip,
             LC_Black,
             xStart + 32, yStart + 20,
             UE4Font,
             DefaultFontScale,
             false
             );
} 

void AMyHUD::DrawHUD_Reset()
{
    ActiveButton_Type = -1;
    ActiveButton_Tip = "";
    CursorHoveringInButton = false;
}

void AMyHUD::DrawHUD()
{
    //Have PC for Mouse Cursor?
    if (!ThePC)
    {
        //Attempt to Reacquire PC
        //ThePC = GetOwningPlayerController();
        
        //Could Not Obtain PC
        //if (!ThePC) return;
    }
    
    //Display the Cursor
    //ThePC->bShowMouseCursor = true;
    
    //Draw HUD?
    if (DontDrawHUD) return;
    
    //Super
    Super::DrawHUD();
    
    //No Canvas?
    if (!Canvas) return;
    
    //Reset States
    DrawHUD_Reset();
    
    //Get New Mouse Position
    //ThePC->GetMousePosition(MouseLocation.X, MouseLocation.Y);
    
    //Cursor In Buttons
    DrawHUD_CheckCursorInButtons();
    
    //Draw Dialogs
    DrawHUD_DrawDialogs();
    
    DrawHealthBar();
    
    if (ActiveButton_Tip != "") DrawToolTip();
}




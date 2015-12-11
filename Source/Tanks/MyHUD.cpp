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
    //PrimaryActorTick.bCanEverTick = true;

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

    DrawRadar();
    
    if (ActiveButton_Tip != "") DrawToolTip();
}


//  Radar things
//  DrawRadar()
//      Draw the circle the radar will sit on. Call DrawOtherPlayers and DrawRadarSweep.
void AMyHUD::DrawRadar()
{
    //  3 == detail of the circle
    int NumPoints = (int)(pow(2,1+3));
    float radar_scale, radar_range, min;
    FVector2D radar_center;
    //  randomly chosen number, change freely
    radar_range = 900.0;
    FVector2D ScreenSize = FVector2D(Canvas->SizeX, Canvas->SizeY);

    //  Radar occupies 1/4 o smaller dimension, perfect circle
    min = (ScreenSize.X > ScreenSize.Y) ? ScreenSize.X:ScreenSize.Y;
    radar_scale = .25 * min * .5;
    radar_center = FVector2D( ScreenSize.X - radar_scale - 15, ScreenSize.Y - radar_scale - 15 );

    //  Draw background circle
    /*
    UTexture2D *texturePtr;
    ConstructorHelpers::FObjectFinder<UTexture2D> textureObj(TEXT("/Game/MapProps/cementColor"));
    if(!textureObj.Object){
        GEngine->AddOnScreenDebugMessage(2, 15.f, FColor::Black, "COULDNT FIND TEXTURE");
        return;
    }
    texturePtr = textureObj.Object;
    Canvas->K2_DrawPolygon(texturePtr, radar_center, FVector2D(radar_scale,radar_scale), NumPoints, FColor(204,255,255,50));
    */
    DrawOtherPlayers(radar_scale, radar_center, radar_range);
    DrawRadarSweep(radar_scale, radar_center);
}
//  DrawOtherPlayers()
//      radar_scale is in screen pixels
//      radar_center is screen coordinate
//      radar_range is world coordinate
//  Draw dots for each nearby "tank"
void AMyHUD::DrawOtherPlayers(float radar_scale, FVector2D radar_center, float radar_range)
{
    FVector2D Me = FVector2D(GetOwningPawn()->GetActorLocation().X, GetOwningPawn()->GetActorLocation().Y);
    FString myName = GetOwningPawn()->GetName();
    GEngine->AddOnScreenDebugMessage(0,2.f,FColor::Blue,myName);
    FVector2D Them;
    FString theirName;
    //  searching for classes AEnemy, ATankCharacter
    FActorIterator ActorItr(GetWorld());
/*
    for(; ActorItr; ++ActorItr){
        theirName = ActorItr->GetName();
        GEngine->AddOnScreenDebugMessage(
            1,1.f,FColor::Red,
            theirName
        );
        if(theirName != myName){
            //  If nearby actor is a tank/enemy
            if( theirName.Contains("Enemy", ESearchCase::IgnoreCase, ESearchDir::FromStart) 
                || theirName.Contains("Tank", ESearchCase::IgnoreCase, ESearchDir::FromStart) 
            ){
                Them = FVector2D(ActorItr->GetActorLocation().X,ActorItr->GetActorLocation().Y);
                //  If the nearby actor is within my radar_range world coordinates
                if( FVector2D::Distance(Me, Them) < radar_range ){
                    Them = Them - Me;
                    Them = Them.GetSafeNormal(.03);
                    Them = Them / radar_range * radar_scale;
                    Them = Them + radar_center;
                    //  Draw a "dot" for them on the minimap
                    DrawLine(
                        FVector(Them.X, Them.Y, 0), 
                        FVector(1,1,1)+FVector(Them.X, Them.Y, 0),
                        FColor(204,255,255),
                        2
                    );
                }
                GEngine->AddOnScreenDebugMessage(
                    2,1.f,FColor::Red,
                    FString::SanitizeFloat(FVector2D::Distance(Me, Them))
                );
            }
        }
        ++ActorItr;
    }
*/
}
//  DrawRadarSweep()
//      radar_scale is in screen pixels
//      radar_center is screen coordinate
//      radar_range is world coordinate
//  Draw a line that spins around the center (like a clock)
void AMyHUD::DrawRadarSweep(float radar_scale, FVector2D radar_center)
{
    static FVector2D sweeper = FVector2D(0,1) * radar_scale;
    float delta = .035;
    float newX, newY;
    newX = sweeper.X * cos(delta) - sweeper.Y * sin(delta);
    newY = sweeper.X * sin(delta) + sweeper.Y * cos(delta);
    sweeper = FVector2D(newX, newY);
    sweeper = sweeper.GetSafeNormal(.03) * radar_scale;
    
    DrawLine(
        FVector(radar_center.X, radar_center.Y, 0), 
        FVector(sweeper.X+radar_center.X, sweeper.Y+radar_center.Y, 0), 
        FColor(204,255,255), 
        1
    );
}
/*  DrawLine(FVector Start, FVector End, FLinearColor TheColor, float Thick)
    *   Draws a line on the screen from Start to End
    *   The line will be color TheColor, ie. FColor::Red
    *   the float is the thickness of the line (in pixels?)
*/
void AMyHUD::DrawLine(FVector Start, FVector End, FLinearColor TheColor, float Thick)
{
   FCanvasLineItem NewLine(Start,End);
   NewLine.SetColor(TheColor);
   NewLine.LineThickness = Thick;
   Canvas->DrawItem(NewLine);
}
